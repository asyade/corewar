#ifndef CPU_H
# define CPU_H

t_int16	params_count(t_byte op);
t_int32	update_invalide_pc(t_process *pc);

void	cpu_fill_stack(t_vm *vm);
void	cpu_process_stack(t_vm *vm);
void	cpu_process_cycle(t_vm *vm);

#endif
