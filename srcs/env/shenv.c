#include "envSh.h"
#include "corewar.h"

# define BASE_HEX_MIN	"0123456789abcdef"

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
	printf("It is now cycle %lld\n", ++total);
}

void			show_consts(t_core *c)
{
	int			i;

	ft_putendl("Introducing contestants...");
	i = -1;
	while (++i < c->vm.champ_count)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1, c->vm.champs[i].header.size, c->vm.champs[i].header.name, c->vm.champs[i].header.comment);
	}
}

int			inst_count(int opcode)
{
	static int	pcount[16] = {
		0,
		2,
		2,
		3,
		3,
		3,
		3,
		3,
		0,
		3,
		3,
		0,
		2,
		3,
		0,
		0
	};
	return (OPVALIDE(opcode)) ? (pcount[opcode - 1]) : -1;
}

char		*inst_names(int opcode)
{
	static char *names[16] = {
		"live",
		"ld",
		"st",
		"add",
		"sub",
		"and",
		"or",
		"xor",
		"zjmp",
		"ldi",
		"sti",
		"fork",
		"lld",
		"lldi",
		"lfork",
		"aff"
	};
	return (OPVALIDE(opcode)) ? (names[opcode - 1]) : NULL;
}

char		*carry_label(t_process *pc)
{
	if (pc->inst[0] & INS_ZJMP)//zjmp todo ?
		return (pc->flags | PF_CARRY) ? "OK" : "KO";
	return ("");
}

void			cb_inst_loaded(t_champ *c, t_process *p)
{
	(void)c;
	(void)p;
	printf("P%5d | %s%s %s\n",  p->id,
		inst_names(p->inst[0]),
		dump_parametters(p->inst, inst_count(p->inst[0])),
		carry_label(p)
	);
	//printf("%d\n", p->inst[0]);
	if (p->inst[0] == 11)
	{
		printf("       | -> store to %d + %d = %d (with pc and mod 100)\n",
			p->inst[3],
			p->inst[4],
			p->inst[3] + p->inst[4]
		);
	}
}

void			cb_pc_updated(t_process *pc)
{
	char 			buffer[1024];
	t_byte			*ptr;
	int				n;
	int				i;

	if (!(sh_env(NULL)->vm.params->verbose & PV_MOVES))
		return ;
	ptr = sh_env(NULL)->vm.memory.mem + pc->cc;
	n = pc->pc - pc->cc;
	i = 0;
	while (n--)
	{
		buffer[i++] = BASE_HEX_MIN[*ptr / 16];
		buffer[i++] = BASE_HEX_MIN[*ptr++ % 16];
		buffer[i++] = ' ';
	}
	buffer[i - 1] = '\0';
	printf("ADV %ld (0x%4.4lx -> 0x%4.4lx) %s\n", pc->pc - pc->cc, pc->cc, pc->pc, buffer);
}

void			she_init(t_core *core)
{
	sh_env(core);
	show_consts(core);
	core->render.instLoaded = (t_instLoaded)&cb_inst_loaded;
	core->render.cycleUpdated = (t_cycleUpdated)&cb_cycle_updated;
	core->render.envDone = (t_envDone)&cb_envdone;
	core->render.playerLive = (t_playerLive)&cb_player_live;
	core->render.livesDelta = (t_livesDelta)&cb_live_delta;
	core->render.processDie = (t_processDie)&cb_pc_die;
	core->render.playerDie = (t_playerDie)&cb_player_die;
	core->render.processLoaded = (t_processLoaded)&cb_pc_loaded;
	core->render.memUpdated = (t_memUpdated)&cb_memUpdated;
	core->render.pcUpdated = (t_pcUpdated)&cb_pc_updated;
}