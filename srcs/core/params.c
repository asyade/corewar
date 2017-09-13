#include "corewar.h"

int		inst_get_code(t_byte code)
{
	static t_int32	ins_table[] = {
		INS_LIVE,
		INS_LD,
		INS_ST,
		INS_ADD,
		INS_SUB,
		INS_AND,
		INS_OR,
		INS_XOR,
		INS_ZJMP,
		INS_LDI,
		INS_STI,
		INS_FORK,
		INS_LLD,
		INS_LLDI,
		INS_LFORK,
		INS_AFF
	};
	return ((code > 0 && code <= 17) ? ins_table[code - 1] : 0);
}

t_int32		param_get_val(t_memory *mem, t_process *pc, t_byte pcode, t_int32 op)
{
	t_int32	val;

	val = 0;
	if (op & INS_LABELNO && pcode == T_IND)
			op = INS_LABEL2;
	if (pcode == T_REG)
		val = mem_readbyte(mem, pc->pc++);
	else if (op & INS_LABEL4)
	{
		val = mem_readint(mem, pc->pc);
		pc->pc += 4;
	}
	else
	{
		val = mem_readshort(mem, pc->pc);
		pc->pc += 2;
	}
	return (val);
}

t_int32		params_read(t_memory *mem, t_process *pc, t_int32 code)
{
	t_byte	i;

	pc->inst[1] = mem_readbyte(mem, pc->pc++);
	if ((i = IP1(pc->inst[1])))
		pc->inst[2] = param_get_val(mem, pc, i, code);
	if (i && (i = IP2(pc->inst[1])))
		pc->inst[3] = param_get_val(mem, pc, i, code);
	if (i && (i = IP3(pc->inst[1])))
		pc->inst[4] = param_get_val(mem, pc, i, code);
	if (i && (i = IP4(pc->inst[1])))
		pc->inst[5] = param_get_val(mem, pc, i, code);
	return (1);
}

t_int32		params_load(t_vm *vm, t_process *pc)
{
	t_int32	code;
	t_vptr	off;

	off = 0;
	if (!(code = inst_get_code(pc->inst[0])))
		return (0);
	if (code & INS_OCTALCODE)
		params_read(&vm->memory, pc, code);
	else if (code == INS_AFF)
	{
		pc->inst[1] = mem_readbyte(&vm->memory, pc->pc);
		off += 1;
	}
	else if (code & INS_LABEL2)
	{
		pc->inst[1] = mem_readshort(&vm->memory, pc->pc);
		off += 2;
	}
	else if (code & (INS_LABEL4))
	{
		pc->inst[1] = mem_readint(&vm->memory, pc->pc);
		off += 4;
	}
	else
	{
		pwarn("0x%2.2x: invalide op definitition", pc->inst[0]);
		return (0);
	}
	pc->pc += off;
	return (1);
}
