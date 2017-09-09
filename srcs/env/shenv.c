#include "envSh.h"
#include "corewar.h"

int				last_live(int nid)
{
	int			tmp;
	static int	id = 0;

	tmp = id;
	id = nid;
	return (tmp);
}

static void		cb_live_delta(int del)
{
	(void)del;
}

static void		cb_pc_die(t_champ *champ)
{
	plog("%s: sub process killed (%d)\n", champ->header.name, champ->nbr_process);
}

static void		cb_pc_loaded(t_champ *champ)
{
	(void)champ;
}

static void		cb_player_die(t_champ *champ)
{
	plog("%s: Die\n", champ->header.name);
}

static void		cb_memUpdated(t_memory *mem, int a, int b)
{
	(void)a;
	(void)b;
	(void)mem;
}

void			cb_player_live(t_champ *c, int id)
{
	if (-id == c->number)
	{
		last_live(-id);
		printf("un processus dit que le joueur %d(%s) est en vie\n", c->number, c->header.name);
	}
}

void			cb_envdone(t_vm *vm)
{
	t_champ		*ch;

	ch = &vm->champs[last_live(0)];
	printf("le joueur %d(%s) a gagne\n", ch->number, ch->header.name);
}

void			she_init(t_core *core)
{
	core->render.envDone = (t_envDone)&cb_envdone;
	core->render.playerLive = (t_playerLive)&cb_player_live;
	core->render.livesDelta = (t_livesDelta)&cb_live_delta;
	core->render.processDie = (t_processDie)&cb_pc_die;
	core->render.playerDie = (t_playerDie)&cb_player_die;
	core->render.processLoaded = (t_processLoaded)&cb_pc_loaded;
	core->render.memUpdated = (t_memUpdated)&cb_memUpdated;
}