/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:30:01 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/20 12:19:11 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_byte	getit(t_process *pc, t_byte pid)
{
	t_byte	t;

	t = 0;
	if (pid == 1)
		t = IP1(pc->inst[1]);
	else if (pid == 2)
		t = IP2(pc->inst[1]);
	else if (pid == 3)
		t = IP3(pc->inst[1]);
	else if (pid == 4)
		t = IP4(pc->inst[1]);
	return (t);
}

t_int32			param_val(t_vm *vm, t_process *pc, t_byte pid)
{
	t_byte	t;

	t = getit(pc, pid);
	if (t == T_DIR)
		return (pc->inst[pid + 1]);
	else if (t == T_IND)
		return (mem_readint(&vm->memory, pc->cc + pc->inst[pid + 1]));//on pars de pc ou cc?
	else if (t == T_REG)
		return (pc->reg[pc->inst[pid + 1] - 1]);
	return (-1);
}

t_int32			param_idxval(t_vm *vm, t_process *pc, t_byte pid)
{
	t_byte	t;

	t = getit(pc, pid);
	if (t == T_DIR)
		return (pc->inst[pid + 1]);
	else if (t == T_IND)
		return (mem_readint(&vm->memory, IDXPTR(pc->cc, pc->inst[pid + 1])));
	else if (t == T_REG)
		return (pc->reg[pc->inst[pid + 1] - 1]);
	return (-1);
}

t_int32			param_dirval(t_process *pc, t_byte pid)
{
	t_byte	t;

	t = getit(pc, pid);
	if (t == T_DIR || t == T_IND)
		return (pc->inst[pid + 1]);
	else if (t == T_REG)
	{
		return (pc->reg[pc->inst[pid + 1] - 1]);
	}
	return (-1);
}
