/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:49 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/14 05:42:22 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_int32		inst_live(t_vm *vm, t_byte ci, t_process *pc)
{
	vm->lives--;
	pc->flags |= PF_LIVEUP;
	if ((-pc->inst[1]) == vm->champs[ci].number)
	{
		vm->champs[ci].flags |= PC_ALIVE;
	}
	if (vm->playerLive)
		(vm->playerLive)(&vm->champs[ci], pc->inst[1]);
	return (1);
}

t_int32		inst_ld(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (!params_chk(PM_DI, PM_R, NULL, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[3] - 1] = param_idxval(vm, pc, 1)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32		inst_st(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (!params_chk(PM_RD, PM_RI, NULL, NULL, pc->inst))
		return (0);
	if (IP2(pc->inst[1]) == T_REG)
		pc->reg[pc->inst[3] - 1] = param_dirval(pc, 1);
	else
		mem_writeint(vm, param_dirval(pc, 1), IDXPTR(pc->cc, param_dirval(pc, 2)), ci + 1);
	return (1);
}

t_int32     inst_add(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	if (!params_chk(PM_R, PM_R, PM_R, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[4] - 1] = param_dirval(pc, 1) + param_dirval(pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32     inst_sub(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	if (!params_chk(PM_R, PM_R, PM_R, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[4] - 1] = param_dirval(pc, 1) - param_dirval(pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32     inst_and(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	(void)vm;
	if (!params_chk(PM_RID, PM_RID, PM_R, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[4] - 1] = param_idxval(vm, pc, 1) & param_idxval(vm, pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);

}

t_int32     inst_or(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	(void)vm;
	if (!params_chk(PM_RID, PM_RID, PM_R, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[4] - 1] = param_idxval(vm, pc, 1) | param_idxval(vm, pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32     inst_xor(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	(void)vm;
	if (!params_chk(PM_RID, PM_RID, PM_R, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[4] - 1] = param_idxval(vm, pc, 1) ^ param_idxval(vm, pc, 2)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32     inst_zjmp(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	if (pc->flags & PF_CARRY)
		pc->pc = IDXPTR(pc->cc, pc->inst[1]);
	return (1);
}

t_int32     inst_ldi(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	(void)pc;
	if (!params_chk(PM_RID, PM_RD, PM_R, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[4] - 1] = mem_readint(&vm->memory, IDXPTR(pc->cc, param_val(vm, pc, 1) + param_dirval(pc, 2)))))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32     inst_sti(t_vm *vm, t_byte ci, t_process *pc)
{
	t_vptr  ptr;

	(void)ci;
	dump_parametters(pc->inst, 3);
	if (!params_chk(PM_R, PM_RID, PM_RID, NULL, pc->inst))
		return (0);
	ptr = IDXPTR(pc->cc, (param_dirval(pc, 2) + param_dirval(pc, 3)));
	mem_writeint(vm, pc->reg[pc->inst[2] - 1], ptr, ci + 1);
	return (1);
}

t_int32			inst_lld(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (!params_chk(PM_DI, PM_R, NULL, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[3] - 1] = param_val(vm, pc, 1)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32			inst_lldi(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (!params_chk(PM_RID, PM_RD, PM_R, NULL, pc->inst))
		return (0);
	if (!(pc->reg[pc->inst[4] - 1] = mem_readint(&vm->memory, param_val(vm, pc, 1) + param_dirval(pc, 2))))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);

}

t_int32			inst_fork(t_vm *vm, t_byte ci, t_process *pc)
{
	t_process     *new;

	new = vm_fork(vm, &vm->champs[ci], IDXPTR(pc->cc, pc->inst[1]));
	ft_memcpy(new->reg, pc->reg, sizeof(t_reg) * REG_NUMBER);
	new->flags = PF_LIVEUP;
	return (1);
}

t_int32			inst_lfork(t_vm *vm, t_byte ci, t_process *pc)
{
	t_process	*new;

	if (!(new = vm_fork(vm, &vm->champs[ci], pc->pc + pc->inst[1])))
		return (0);
	ft_memcpy(new->reg, pc->reg, sizeof(t_reg) * REG_NUMBER);
	new->flags = pc->flags;
	return (1);
}

t_int32     inst_aff(t_vm *vm, t_byte ci, t_process *pc)
{
	if (!params_chk(PM_R, NULL, NULL, NULL, pc->inst))
		return (0);
	(void)vm;
	(void)ci;
	(void)pc;
	return (1);
}
