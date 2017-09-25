/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:49 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/25 16:40:07 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_int32		inst_live(t_vm *vm, t_byte ci, t_process *pc)
{
	vm->lives--;
	pc->flags |= PF_LIVEUP;
	pc->last_live = 0;
	if ((-pc->inst[1]) == vm->champs[ci].number)
	{
		vm->champs[ci].flags &= ~PC_YOUNG;
		vm->champs[ci].flags |= PC_ALIVE;
	}
	if (vm->playerLive)
		(vm->playerLive)(&vm->champs[ci], pc->inst[1]);
	return (1);
}

t_int32		inst_zjmp(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	if (pc->flags & PF_CARRY)
	{
		pc->pc = IDXPTR(pc->cc, pc->inst[1]);
	}
	return (1);
}

t_int32		inst_aff(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	(void)pc;
	if (!(vm->params->flag & P_SHOWAFF))
		return (1);
	printf("Aff: %c\n", param_dirval(pc, 1) % 256);
	return (1);
}
