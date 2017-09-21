#include "corewar.h"

t_byte		param_get_size(t_byte opcode, t_byte type)
{
	if (type == T_IND)
		return (2);
	if (type == T_DIR)
	{
		if (op_tab[opcode - 1].label_size == 0)
			return (4);
		else
			return (2);
	}
	return (type == T_REG ? 1 : 0);
}

t_int32		param_get_val(t_memory *mem, t_process *pc, t_byte type)
{
	if (type == T_REG)
		return (mem_readbyte(mem, pc->pc++));
	else if (param_get_size(pc->inst[0], type) == 4)
	{
		pc->pc += 4;
		return (mem_readint(mem, pc->pc - 4));
	}
	pc->pc += 2;
	return (mem_readshort(mem, pc->pc - 2));
}
