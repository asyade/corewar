#include "corewar.h"

static t_int16	param_size(t_byte op, t_byte code)
{
	int		m;

	m = inst_get_code(op);
	if (!code)
		return (0);
	if (code == T_REG)
		return (1);
	if (m & INS_LABELNO && code == T_IND)
		m = INS_LABEL2; 
	if (m & INS_LABEL2)
		return (2);
	if (m & INS_LABEL4)
		return (4);
	return (0);
}

t_int16			params_count(t_byte opcode)
{
	static int	pcounts[] = {
		1,
		2,
		2,
		3,
		3,
		3,
		3,
		3,
		1,
		3,
		3,
		1,
		2,
		3,
		1,
		1
	};
	if (!(OPVALIDE(opcode)))
		return (0);
	return (pcounts[opcode - 1]);
}

t_int32			update_invalide_pc(t_process *pc)
{
	t_int16	count;
	t_int16	delta;

	delta = 0;
	if (pc->inst[1] == 0x00)
		return (0);
	count = params_count(pc->inst[0]);
	if (count >= 1)
		delta += param_size(pc->inst[0], IP1(pc->inst[1]));
	if (count >= 2)
		delta += param_size(pc->inst[0], IP2(pc->inst[1]));
	if (count >= 3)
		delta += param_size(pc->inst[0], IP3(pc->inst[1]));
	if (count >= 4)
		delta += param_size(pc->inst[0], IP4(pc->inst[1]));
	pc->pc = pc->cc;
	pc->pc += delta + 2;
	return (delta);
}