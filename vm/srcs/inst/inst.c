/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:49 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 04:28:07 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_int32		inst_live(t_vm *vm, t_byte ci, t_process *pc)
{
	int		i;

	if (vm->lives > 0)
		vm->lives--;
	pc->flags |= PF_LIVEUP;
	pc->last_live = 0;
	if ((-pc->inst[1]) == vm->champs[ci].number)
	{
		if (vm->params->flag & P_SOUND)
			vm_live_sound();
		vm->champs[ci].nbr_live++;
		i = -1;
		vm->champs[ci].flags &= ~PC_YOUNG;
		while (++i < vm->champ_count)
			vm->champs[i].flags &= ~PC_ALIVE;
		vm->champs[ci].flags |= PC_ALIVE;
	}
	if (vm->player_live)
		(vm->player_live)(&vm->champs[ci], pc->inst[1]);
	return (1);
}

t_int32		inst_zjmp(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	if (pc->flags & PF_CARRY)
	{
		if (vm->params->flag & P_SOUND)
			vm_jump_sound();
		pc->pc = IDXPTR(pc->cc, pc->inst[1]);
	}
	return (1);
}

t_int32		inst_aff(t_vm *vm, t_byte ci, t_process *pc)
{
	static char	buffer[2];

	(void)ci;
	(void)pc;
	if (!(vm->params->flag & P_SHOWAFF))
		return (1);
	ft_static_put("Aff: ", sizeof("Aff: ") - 1, 0);
	buffer[0] = param_dirval(pc, 1) % 256;
	buffer[1] = '\n';
	ft_static_put(buffer, 2, 0);
	return (1);
}
