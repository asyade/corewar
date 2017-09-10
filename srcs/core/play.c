/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:35:54 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/11 00:31:11 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void     play_load_champs(t_vm *vm)
{
	t_int32         i;
	t_vptr          offset;
	t_process       *pc;

	i = vm->champ_count;
	while (i--)
	{
		offset = i * (MEM_SIZE / vm->champ_count);
		vm_load_champ(vm, &vm->champs[i], offset);
		pc = vm_fork(vm, &vm->champs[i], offset);
		pc->reg[0] = -vm->champs[i].number;
		vm->champs[i].flags = PC_ALIVE | PC_LOADED;
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
		else
			vm_kill(vm, ci, pc);
	}
	if (!count && !(champ->flags | PC_DIE))
	{
		champ->flags |= PC_DIE;
		if (vm->playerDie)
			(vm->playerDie)(champ);
	}
	if (champ->flags & PC_ALIVE)
	{
		champ->flags &= ~PC_ALIVE;
		return (1);
	}
	return (0);
}

t_byte     play_check_champs(t_core *core)
{
	int    ci;
	int    ret;
	int    avc;

	avc = 0;
	ci = -1;
	ret = 0;
	if (core->vm.lives <= 0)
	{
		core->vm.lives = NBR_LIVE;
		core->vm.cycles_to_die -= CYCLE_DELTA;
		if (core->vm.cycles_to_die < 1)
			core->vm.cycles_to_die = 0;
	}
	core->vm.cycles = core->vm.cycles_to_die;
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

/*
** A voire si c'est pas du sucide de faire une recursive ici
** Aucune allocatiosion sur la stack sa passe ou pas ? O_o
** Au pire deux petite while
*/

void            play_recursive(t_core *core)
{
	while (--core->vm.cycles)
		cpu_process_cycle(&core->vm);
	if (core->vm.lives <= 0)
	{
		core->vm.cycles_to_die -= CYCLE_DELTA;
		core->vm.lives = NBR_LIVE;
	}
	core->vm.cycles = core->vm.cycles_to_die;
	if (play_check_champs(core))
		play_recursive(core);
}

t_byte          play(t_core *core)
{
	if (core->vm.cycleUpdated)
		(core->vm.cycleUpdated)();
	core->vm.lives = NBR_LIVE;
	core->vm.cycles_to_die = CYCLE_TO_DIE;
	core->vm.cycles = CYCLE_TO_DIE;
	play_load_champs(&core->vm);
	play_recursive(core);
	if (core->vm.cycleUpdated)
		(core->vm.cycleUpdated)();
	return (1);//TODO:winer id
}