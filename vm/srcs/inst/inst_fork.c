#include "corewar.h"

static void		do_fork(t_vm *vm, t_process *pc, t_vptr offset, t_byte ci)
{
	t_process	*new;
	
	new = vm_fork(vm, &vm->champs[ci], offset);
	ft_memcpy(new->reg, pc->reg, sizeof(t_reg) * REG_NUMBER);
	new->flags = pc->flags;	
	cpu_pc_process(vm, ci, new);//A voir si c'est correct, on pars du principe que la vm execute le champion forked dans le cycle du fork
}

t_int32			inst_fork(t_vm *vm, t_byte ci, t_process *pc)
{
	do_fork(vm, pc, IDXPTR(pc->cc, pc->inst[1]), ci);
	return (1);
}

t_int32			inst_lfork(t_vm *vm, t_byte ci, t_process *pc)
{
	do_fork(vm, pc, pc->cc + pc->inst[1], ci);
	return (1);
}