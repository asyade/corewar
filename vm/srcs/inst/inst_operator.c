/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:09:18 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_int32		inst_add(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	if (!(pc->reg[pc->inst[4] - 1] = param_dirval(pc, 1) + param_dirval(pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32		inst_sub(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	if (!(pc->reg[pc->inst[4] - 1] = param_dirval(pc, 1) -
			param_dirval(pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32		inst_and(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	(void)vm;
	if (!(pc->reg[pc->inst[4] - 1] = param_idxval(vm, pc, 1) &
			param_idxval(vm, pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32		inst_or(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	(void)vm;
	if (!(pc->reg[pc->inst[4] - 1] = param_idxval(vm, pc, 1) |
			param_idxval(vm, pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32		inst_xor(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	(void)vm;
	if (!(pc->reg[pc->inst[4] - 1] = param_idxval(vm, pc, 1) ^
			param_idxval(vm, pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}
