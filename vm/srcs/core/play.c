/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:35:54 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/25 16:39:30 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void     play_load_champs(t_vm *vm)
{
	t_int32		i;
	t_vptr		offset;
	t_process	*pc;

	i = vm->champ_count;
	while (i--)
	{
		offset = i * (MEM_SIZE / vm->champ_count);
		vm_load_champ(vm, &vm->champs[i], offset);
		pc = vm_fork(vm, &vm->champs[i], offset);
		pc->reg[0] = -vm->champs[i].number;
		vm->champs[i].flags = PC_LOADED | PC_ALIVE | PC_YOUNG;
	}
}

t_byte     play_is_alive(t_vm *vm, t_champ *champ, int ci)
{
	t_process   *pc;
	int         count;
	t_process   *tmp;

	count = 0;
	tmp = champ->process;
	while (tmp)
	{
		pc = tmp;
		tmp = tmp->next;
		if (pc->flags & PF_LIVEUP)
		{
			pc->flags &= ~PF_LIVEUP;
			count++;
		}
		else/*  if (!(champ->flags & PC_ALIVE)/\*  && pc->last_live >= vm->cycles_to_die * 2 *\/) */
		{
			if (vm->processDie)
				vm->processDie(champ, pc);
			vm_kill(vm, ci, pc);
		}
	}
	if (!count && !(champ->flags | PC_DIE))
	{
		champ->flags |= PC_DIE;
		if (vm->playerDie)
			(vm->playerDie)(champ);
	}
	if (champ->flags & PC_ALIVE)
	{
		if (champ->flags & PC_YOUNG)
		{
			champ->flags &= ~PC_YOUNG;
			return (count > 0 ? 1 : 0);		
		}
		champ->flags &= ~PC_ALIVE;
		return (1);
	}
	return (count > 0 ? 1 : 0);
}

t_byte			play_check_champs(t_core *core)
{
	int    ci;
	int    ret;
	int    avc;

	avc = 0;
	ci = -1;
	ret = 0;
	while (++ci < core->vm.champ_count)
	{
		if (play_is_alive(&core->vm, &core->vm.champs[ci], ci))
		{
			core->vm.champs[ci].flags &= ~PC_ALIVE;
			avc++;
			ret = ci;
		}
	}
	if (avc == 1 && core->render.playerWin)
		(core->render.playerWin)(&core->vm.champs[ret]);
	return (avc);
}

void			play_loop(t_core *core)
{
	while (core->vm.cycles--)
	{
		if (core->vm.cycleUpdated)
			(core->vm.cycleUpdated)();
		cpu_process_cycle(&core->vm);
	}
	if (core->vm.lives <= 0 || ++core->vm.nbr_check >= MAX_CHECKS)
	{
		core->vm.nbr_check = 0;
		core->vm.cycles_to_die -= CYCLE_DELTA;
		core->vm.cycles_to_die = (core->vm.cycles_to_die) <= 0 ? 1 : core->vm.cycles_to_die;
		core->vm.lives = NBR_LIVE;
		if (core->render.cycleToDieDelta)
			(core->render.cycleToDieDelta)(core->vm.cycles_to_die);
	}
	core->vm.cycles = core->vm.cycles_to_die;
}

t_byte			play(t_core *core)
{
	core->vm.lives = NBR_LIVE;
	core->vm.cycles_to_die = CYCLE_TO_DIE/*  + 2 */;
	core->vm.cycles = CYCLE_TO_DIE;
	play_load_champs(&core->vm);
	while (1)
	{
		play_loop(core);
		if (!play_check_champs(core))
			break ;
	}
	return (1);//TODO:winer id
}
