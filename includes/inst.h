#ifndef INST_H
# define INST_H

# include "def.h"

/*
**	TODO: Et la lumière fut
*/

# define INS_OCTALCODE	0xB6FE
# define INS_LABEL2		0x6F04//0x6F24//0x6F04
# define INS_LABEL4		0x10E3//0x10C3//0x10E3
# define INS_LABELNO	0x80FE//0x803E//0x801E

# define INS_GETCARRY	(INS_ZJMP)

# define INS_LIVE		0x0001
# define INS_LD			0x0002
# define INS_ST			0x0004
# define INS_ADD		0x0008
# define INS_SUB		0x0010
# define INS_AND		0x0020
# define INS_OR			0x0040
# define INS_XOR		0x0080
# define INS_ZJMP		0x0100
# define INS_LDI		0x0200
# define INS_STI		0x0400
# define INS_FORK		0x0800
# define INS_LLD		0x1000
# define INS_LLDI		0x2000
# define INS_LFORK		0x4000
# define INS_AFF		0x8000

/*
** Cut parammeters encoding octet in for couple of 2 bits
** the value of theses 2 bits gonna be T_IND or T_REG or T_DIR
*/

# define IP1(c)	((c & 0xC0) >> 6)
# define IP2(c)	((c & 0x30) >> 4)
# define IP3(c)	((c & 0xC) >> 2)
# define IP4(c)	(c & 0x3)

/*
** parametters mask
** R = T_REG, I = T_IND, D = T_DIR
*/

# define PM_R	(t_byte[3]){ T_REG, 0, 0 }
# define PM_I	(t_byte[3]){ T_IND, 0, 0 }
# define PM_D	(t_byte[3]){ T_DIR, 0, 0 }
# define PM_RI	(t_byte[3]){ T_IND, T_REG, 0 }
# define PM_RD	(t_byte[3]){ T_DIR, T_REG, 0 }
# define PM_DI	(t_byte[3]){ T_DIR, T_IND, 0 }
# define PM_RID	(t_byte[3]){ T_DIR, T_IND, T_REG}

# define OPVALIDE(op)	(op >= 1 && op <= 16)
# define REGVALIDE(reg)	(reg >= 1 && reg <= 16)

# define IDXPTR(pc, ptr) (pc + (ptr % IDX_MOD))


int				inst_get_code(t_byte code);
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
t_int32			params_load(t_vm *vm, t_process *pc);
typedef t_int32	(*t_inst)(t_vm *, t_byte ci, t_process *pc);

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