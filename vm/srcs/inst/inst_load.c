#include "corewar.h"

t_int32			inst_ld(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (!(pc->reg[pc->inst[3] - 1] = param_idxval(vm, pc, 1)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32			inst_ldi(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)vm;
	(void)ci;
	(void)pc;
	if (!(pc->reg[pc->inst[4] - 1] = mem_readint(&vm->memory, IDXPTR(pc->cc, param_val(vm, pc, 1) + param_dirval(pc, 2)))))
		;
/* 		pc->flags |= PF_CARRY; */
/* 	else */
/* 		pc->flags &= ~PF_CARRY; */
	return (1);
}

t_int32			inst_lld(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (!(pc->reg[pc->inst[3] - 1] = param_val(vm, pc, 1)))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}

t_int32			inst_lldi(t_vm *vm, t_byte ci, t_process *pc)
{
	(void)ci;
	if (!(pc->reg[pc->inst[4] - 1] = mem_readint(&vm->memory, pc->cc + param_val(vm, pc, 1) + param_dirval(pc, 2))))
		pc->flags |= PF_CARRY;
	else
		pc->flags &= ~PF_CARRY;
	return (1);
}
