/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 03:56:18 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
** process.c
*/

t_process	*pc_new(t_reg number);
void		pc_push(t_process **root, t_process *pc);
void		pc_remove(t_process **root, t_process *pc);
void		pc_clear(t_process *root);

/*
** vm.c
*/

void		vm_kill_sound(void);
void		vm_jump_sound(void);
void		vm_live_sound(void);
void		vm_sound_ambient(int stop);

void		vm_init(t_vm *vm);
void		vm_load_champ(t_vm *vm, t_champ *champ, t_vptr offset);
t_process	*vm_fork(t_vm *vm, t_champ *champ, t_vptr offset);
void		vm_kill(t_vm *vm, t_process *pc);
void		dump(t_vm *vm);

#endif
