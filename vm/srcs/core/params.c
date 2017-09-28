/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:03:32 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_int32		params_read(t_memory *mem, t_process *pc)
{
	t_byte	i;

	if (pc->inst[1] == 0x00)
		return (0);
	if ((i = IP1(pc->inst[1])))
		pc->inst[2] = param_get_val(mem, pc, i);
	if (i && (i = IP2(pc->inst[1])))
		pc->inst[3] = param_get_val(mem, pc, i);
	if (i && (i = IP3(pc->inst[1])))
		pc->inst[4] = param_get_val(mem, pc, i);
	if (i && (i = IP4(pc->inst[1])))
		pc->inst[5] = param_get_val(mem, pc, i);
	return (1);
}

t_int32		params_load(t_vm *vm, t_process *pc)
{
	g_op_tab[pc->inst[0] - 1].called = 1;
	if (g_op_tab[pc->inst[0] - 1].octal_code == 1)
	{
		pc->inst[1] = mem_readbyte(&vm->memory, pc->pc++);
		if (params_check_correct(pc))
			params_read(&vm->memory, pc);
		else
			return (0);
		if (!params_check_register(pc))
			return (0);
	}
	else if (g_op_tab[pc->inst[0] - 1].arg_type[0] == T_REG)
		pc->inst[1] = mem_readbyte(&vm->memory, pc->pc++);
	else if (param_get_size(pc->inst[0],
				g_op_tab[pc->inst[0] - 1].arg_type[0]) == 2)
	{
		pc->inst[1] = mem_readshort(&vm->memory, pc->pc);
		pc->pc += 2;
	}
	else
	{
		pc->inst[1] = mem_readint(&vm->memory, pc->pc);
		pc->pc += 4;
	}
	return (1);
}
