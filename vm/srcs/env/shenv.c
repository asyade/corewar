/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 13:56:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/26 07:09:00 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envSh.h"
#include "corewar.h"

# define BASE_HEX_MAJ	"0123456789abcdef"

t_core			*sh_env(t_core *c)
{
	static	t_core	*core;

	if (c)
		core = c;
	return (core);
}

static void		cb_memUpdated(t_memory *m, int a, int b)
{
	(void)m;
	(void)a;
	(void)b;
}

static void		cb_live_delta(int del)
{
	(void)del;
}

static void		cb_pc_die(t_champ *champ, t_process *pc)
{
	(void)champ;
	if (params()->verbose & PV_DEATH)
		printf("Process %d hasn't lived for %ld cycles (CTD %d)\n", pc->id, pc->last_live, sh_env(NULL)->vm.cycles_to_die);
}

static void		cb_pc_loaded(t_champ *champ)
{
	(void)champ;
}

static void		cb_player_die(t_champ *champ)
{
	plog("%s: Die\n", champ->header.name);
}

void			cb_player_live(t_champ *c, int id)
{
	if (!(params()->verbose & PV_LIVES))
		return ;
	if (-id == c->number)
		printf("Player %d (%s) is said to be alive\n", c->number, c->header.name);
}

void			dump_inst_called(void)
{
	int			i;

	i = -1;

	ft_putendl("the following instructions have been used :\n");
	while (++i < OP_NBR)
	{
		if (op_tab[i].called)
		{
			ft_putendl(op_tab[i].name);
		}
	}
}

void			cb_envdone(t_vm *vm)
{
	t_champ		*ch;
	int			i;

	if (vm->params->verbose & PV_DMPINST)
		dump_inst_called();
	i = -1;
	ch = &vm->champs[vm->winner];
	printf("Contestant %d, \"%s\", has won !\n", ch->number, ch->header.name);
}

void			cb_cycle_updated(void)
{
	static long long int	total = 0;
	t_vm					*vm;

	vm = &sh_env(NULL)->vm;
	total++;
	if (vm->params->verbdellay != -1 && --vm->params->verbdellay > 0)
		return ;
	if (!(vm->params->verbose & PV_CYCLES))
		return ;
	printf("It is now cycle %lld\n", total);
}

void			show_consts(t_core *c)
{
	int			i;

	printf("Introducing contestants...\n");
	i = -1;
	while (++i < c->vm.champ_count)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1, c->vm.champs[i].header.size, c->vm.champs[i].header.name, c->vm.champs[i].header.comment);
	}
}

int			inst_count(int opcode)
{
	static int	pcount[16] = { 0, 2, 2, 3, 3, 3, 3, 3, 0, 3, 3, 0, 2, 3, 0, 0 };
	return (OPVALIDE(opcode)) ? (pcount[opcode - 1]) : -1;
}

char		*carry_label(t_process *pc)
{
	static char	buff[1024];
	if (pc->inst[0] == 9)
		return (pc->flags & PF_CARRY) ? " OK" : " FAILED";
	if (pc->inst[0] == 12 || pc->inst[0] == 15)
	{
		buff[0] = '\0';
		sprintf(buff, " (%ld)",(pc->inst[0] == 15) ?  pc->cc + pc->inst[1] : IDXPTR(pc->cc, pc->inst[1]));
		return (buff);
	}
	return ("");
}

void			cb_inst_loaded(t_champ *c, t_process *p)
{
	(void)c;
	(void)p;
	if (p->inst[0] == 16)
		return ;
	printf("P%5d | %s%s%s\n",  p->id,
		op_tab[p->inst[0] - 1].name,
		   dump_parametters(&sh_env(NULL)->vm, p, inst_count(p->inst[0])),
		carry_label(p)
	);
	if (p->inst[0] == 11)
	{
		printf("       | -> store to %d + %d = %d (with pc and mod %ld)\n",
			param_dirval(p, 2),
			param_dirval(p, 3),
			param_dirval(p, 2) + param_dirval(p, 3),
			p->cc + param_dirval(p, 2) + param_dirval(p, 3));
	}
	else if (p->inst[0] == 10)
	{
		printf("       | -> load from %d + %d = %d (with pc and mod %ld)\n",
			param_dirval(p, 1),
			param_dirval(p, 2),
			param_dirval(p, 1) + param_dirval(p, 2),
			IDXPTR(p->cc, param_dirval(p, 1) + param_dirval(p, 2))
		);
	}
}

void			cb_pc_updated(t_process *pc)//ICI segfault a refaire !!
{
	char 			buffer[1024 * 4 * 8];
	char			*ptr;
	t_vptr			i;
	t_memory		*mem;

	if (!(sh_env(NULL)->vm.params->verbose & PV_MOVES) || (pc->inst[0] == 9 && pc->flags & PF_CARRY))
		return ;
	mem = &sh_env(NULL)->vm.memory;
	i = pc->cc;
	ptr = buffer;
	if (labs(pc->zc - i) > 500)
		return ;
	while (i < pc->zc)
	{
		*ptr++ = BASE_HEX_MAJ[mem_readbyte(mem, i) / 16];
		*ptr++ = BASE_HEX_MAJ[mem_readbyte(mem, i++) % 16];
		*ptr++ = ' ';
	}
	*ptr = '\0';
	printf("ADV %ld (0x%4.4lx -> 0x%4.4lx) %s\n", pc->zc - pc->cc, pc->cc, pc->zc, buffer);
}

void			cb_cycle_to_die_delta(int ctd)
{
	if (sh_env(NULL)->vm.params->verbose & PV_CYCLES)
		printf("Cycle to die is now %d\n", ctd);
}

void			she_init(t_core *core)
{
	sh_env(core);
	show_consts(core);
	core->render.cycleToDieDelta = &cb_cycle_to_die_delta;
	core->render.instLoaded = (t_instLoaded)&cb_inst_loaded;
	core->render.cycleUpdated = (t_cycleUpdated)&cb_cycle_updated;
	core->render.envDone = (t_envDone)&cb_envdone;
	core->render.playerLive = (t_playerLive)&cb_player_live;
	core->render.livesDelta = (t_livesDelta)&cb_live_delta;
	core->render.processDie = (t_processDie)&cb_pc_die;
	core->render.playerDie = (t_playerDie)&cb_player_die;
	core->render.processLoaded = (t_processLoaded)&cb_pc_loaded;
	core->render.pcUpdated = (t_pcUpdated)&cb_pc_updated;
	core->render.memUpdated = (t_memUpdated)cb_memUpdated;
}
