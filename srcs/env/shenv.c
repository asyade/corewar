#include "envSh.h"
#include "corewar.h"

t_core			*sh_env(t_core *c)
{
	static	t_core	*core;

	if (c)
		core = c;
	return (core);
}

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
	if (!(params()->verbose & PV_LIVES))
		return ;
	if (-id == c->number)
	{
		last_live(-id);
		printf("Player %d (%s) is said to be alive\n", c->number, c->header.name);
	}
}

void			cb_envdone(t_vm *vm)
{
	t_champ		*ch;

	ch = &vm->champs[last_live(0)];
	printf("Contestant %d, \"%s\", has won !\n", ch->number, ch->header.name);
}

void			cb_cycle_updated(void)
{
	static long long int	total = 0;

	if (!(sh_env(NULL)->vm.params->verbose & PV_CYCLES))
		return ;
	printf("Is now the cycle %lld\n", ++total);
}

void			show_consts(t_core *c)
{
	int			i;

	ft_putendl("Introducing contestants...");
	i = -1;
	while (++i < c->vm.champ_count)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i, c->vm.champs[i].header.size, c->vm.champs[i].header.name, c->vm.champs[i].header.comment);
	}
}

void			she_init(t_core *core)
{
	sh_env(core);
	show_consts(core);
	core->render.cycleUpdated = (t_cycleUpdated)&cb_cycle_updated;
	core->render.envDone = (t_envDone)&cb_envdone;
	core->render.playerLive = (t_playerLive)&cb_player_live;
	core->render.livesDelta = (t_livesDelta)&cb_live_delta;
	core->render.processDie = (t_processDie)&cb_pc_die;
	core->render.playerDie = (t_playerDie)&cb_player_die;
	core->render.processLoaded = (t_processLoaded)&cb_pc_loaded;
	core->render.memUpdated = (t_memUpdated)&cb_memUpdated;
}