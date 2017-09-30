/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:39:01 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/26 09:19:29 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "def.h"

static void		do_fork(t_vm *vm, t_process *pc, t_vptr offset, t_byte ci)
{
	t_process	*new;

	new = vm_fork(vm, &vm->champs[ci], offset);
	ft_memcpy(new->reg, pc->reg, sizeof(t_reg) * REG_NUMBER);
	new->champ_index = pc->champ_index;
	new->last_live = pc->last_live - 1;
	new->flags = pc->flags;
	cpu_pc_process(vm, ci, new);
}

t_int32			inst_fork(t_vm *vm, t_byte ci, t_process *pc)
{
	do_fork(vm, pc, IDXPTR(pc->cc, pc->inst[1]), ci);
	return (1);
}

t_int32			inst_lfork(t_vm *vm, t_byte ci, t_process *pc)
{
	do_fork(vm, pc, ABSPTR(MEMPTR(pc->cc + pc->inst[1])), ci);
	return (1);
}
