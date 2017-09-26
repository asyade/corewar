/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:35:54 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 05:06:45 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void     play_load_champs(t_vm *vm)
{
	t_int32		i;
	t_vptr		offset;
	t_process	*pc;

	i =  0;
	while (i < vm->champ_count)
	{
		offset = i * (MEM_SIZE / vm->champ_count);
		vm_load_champ(vm, &vm->champs[i], offset);
		pc = vm_fork(vm, &vm->champs[i], offset);
		pc->reg[0] = -vm->champs[i].number;
		pc->champ_index = i;
		vm->champs[i].flags |= PC_ALIVE;/*  | PC_YOUNG */;
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
			ret = 1;
		}
		else
		{
			if (vm->processDie)
				vm->processDie(&vm->champs[0], tmp);
			vm_kill(vm, 0, tmp);
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_byte			play_check_champs(t_core *core)
{
	int		ret;

	ret = play_check_process(&core->vm);
	if (!ret && core->render.playerWin)
		(core->render.playerWin)(&core->vm.champs[ret]);
	return (ret);
}

void			play_loop(t_core *core)
{
	while (core->vm.cycles--)
	{
		if (core->vm.cycleUpdated)
			(core->vm.cycleUpdated)();
		cpu_process_cycle(&core->vm);
	}
}

uint32_t		ft_is_one_champ_live_breakdown(t_core *core)
{
	uint32_t	i;

	i = 0;
	while (i < core->vm.champ_count)
	{
		if (!core->vm.champs[i].nbr_live)
			return (1);
		i++;
	}
	return (0);
}

t_byte			play(t_core *core)
{
	uint32_t	i;

	core->vm.lives = NBR_LIVE;
	core->vm.cycles_to_die = CYCLE_TO_DIE;
	core->vm.cycles = CYCLE_TO_DIE;
	core->vm.nbr_check = 0;
	play_load_champs(&core->vm);
	while (1)
	{
		i = 0;
		while (i < core->vm.champ_count)
		{
			core->vm.champs[i].nbr_live = NBR_LIVE;
			i++;
		}
		play_loop(core);
		if (!play_check_champs(core))
			break ;
		if (ft_is_one_champ_live_breakdown(core) || ++core->vm.nbr_check >= MAX_CHECKS)
		{
			core->vm.nbr_check = 0;
			core->vm.cycles_to_die -= CYCLE_DELTA;
//			core->vm.lives = NBR_LIVE;
			if (core->render.cycleToDieDelta)
				(core->render.cycleToDieDelta)(core->vm.cycles_to_die);
		}
		core->vm.cycles = core->vm.cycles_to_die < 0 ? 1 : core->vm.cycles_to_die;
	}
	return (1);//TODO:winer id
}
