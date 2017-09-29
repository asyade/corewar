/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:49 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:18:19 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_int32		inst_st(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (IP2(pc->inst[1]) == T_REG)
		pc->reg[pc->inst[3] - 1] = param_dirval(pc, 1);
	else
		mem_writeint(vm, param_dirval(pc, 1),
						IDXPTR(pc->cc, param_dirval(pc, 2)), ci + 1);
	return (1);
}

t_int32		inst_sti(t_vm *vm, t_byte ci, t_process *pc)
{
	t_vptr	ptr;

	(void)ci;
	ptr = IDXPTR(pc->cc, (param_dirval(pc, 2) + param_dirval(pc, 3)));
	mem_writeint(vm, pc->reg[pc->inst[2] - 1], ptr, ci + 1);
	return (1);
}
