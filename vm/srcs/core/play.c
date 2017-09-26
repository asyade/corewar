/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:35:54 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 10:08:00 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		play_load_champs(t_vm *vm)
{
	t_int32		i;
	t_vptr		offset;
	t_process	*pc;

	i = 0;
	while (i < vm->champ_count)
	{
		offset = i * (MEM_SIZE / vm->champ_count);
		vm_load_champ(vm, &vm->champs[i], offset);
		pc = vm_fork(vm, &vm->champs[i], offset);
		pc->reg[0] = -vm->champs[i].number;
		pc->champ_index = i;
		vm->champs[i].flags |= PC_ALIVE | PC_YOUNG;
		i++;
	}
}

int				play_check_process(t_vm *vm)
{
	t_process		*tmp;
	int				ret;

	ret = 0;
	tmp = vm->process;
	while (tmp)
	{
		if (tmp->flags & PF_LIVEUP)
		{
			tmp->flags &= ~PF_LIVEUP;
			ret = tmp->champ_index + 1;
		}
		else
		{
			if (vm->process_die)
				vm->process_die(&vm->champs[0], tmp);
			vm_kill(vm, tmp);
		}
		tmp = tmp->next;
	}
	return (ret);
}

void			play_loop(t_core *core)
{
	while (core->vm.cycles--)
	{
		if (core->vm.cycle_updated)
			(core->vm.cycle_updated)();
		cpu_process_cycle(&core->vm);
	}
}

t_byte			play(t_core *core)
{
	int			ret;

	core->vm.lives = NBR_LIVE;
	core->vm.cycles_to_die = CYCLE_TO_DIE;
	core->vm.cycles = CYCLE_TO_DIE;
	core->vm.nbr_check = 0;
	play_load_champs(&core->vm);
	while (1)
	{
		core->vm.lives = NBR_LIVE;
		play_loop(core);
		if (!(ret = play_check_process(&core->vm)))
			break ;
		if (!core->vm.lives || ++core->vm.nbr_check >= MAX_CHECKS)
		{
			core->vm.nbr_check = 0;
			core->vm.cycles_to_die -= CYCLE_DELTA;
			if (core->render.cycle_delta)
				(core->render.cycle_delta)(core->vm.cycles_to_die);
		}
		core->vm.cycles = core->vm.cycles_to_die < 0 ? 1 :
core->vm.cycles_to_die;
	}
	return (ret);
}
