#ifndef INST_H
# define INST_H

# include "def.h"

/*
** Cut parammeters encoding octet in for couple of 2 bits
** the value of theses 2 bits gonna be T_IND or T_REG or T_DIR
*/

# define IP1(c)	((c & 0xC0) >> 6)
# define IP2(c)	((c & 0x30) >> 4)
# define IP3(c)	((c & 0xC) >> 2)
# define IP4(c)	(c & 0x3)

typedef t_int32	(*t_inst)(t_vm *, t_byte ci, t_process *pc);

typedef char			t_arg_type;

typedef struct			s_op
{
	char				*name;
	uint64_t			nbr_arg;
	t_arg_type			*arg_type;
	uint8_t				opcode;
	char				pad[7];
	uint64_t			nbr_cycles;
	char				*describ;
	uint32_t			octal_code;
	uint32_t			label_size;
	t_inst				call;
	char				called;
}						t_op;

extern	t_op			op_tab[OP_NBR];

# define OPVALIDE(op)	(op >= 1 && op <= 16)
# define REGVALIDE(reg)	(reg >= 1 && reg <= 16)

# define IDXPTR(pc, ptr) (pc + (ptr % IDX_MOD))


t_byte			params_chk(t_byte a[3], t_byte b[3], t_byte c[3], t_byte d[3], t_int32 inst[6]);

/*
** if T_IND read 4 byte at IDX(val), else param_dirval
*/
t_int32			param_val(t_vm *vm, t_process *pc, t_byte pid);
t_int32			param_idxval(t_vm *vm, t_process *pc, t_byte pid);

/*
**  get numeric value or register value
*/
t_int32			param_dirval(t_process *pc, t_byte pid);


t_byte			param_get_size(t_byte opcode, t_byte type);
t_int32			param_get_val(t_memory *mem, t_process *pc, t_byte type);
t_int32			params_check_correct(t_process *pc);
t_int32			params_check_register(t_process *pc);
t_int32			params_load(t_vm *vm, t_process *pc);

t_int32			inst_live(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_ld(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_st(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_add(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_sub(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_and(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_or(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_xor(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_zjmp(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_ldi(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_sti(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_fork(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_lld(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_lldi(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_lfork(t_vm *vm, t_byte ci, t_process *pc);
t_int32			inst_aff(t_vm *vm, t_byte ci, t_process *pc);

#endif
