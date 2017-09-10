/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/10 02:10:21 by acorbeau         ###   ########.fr       */
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

void		vm_init(t_vm *vm);;
void		vm_load_champ(t_vm *vm, t_champ *champ, t_vptr offset);
void		vm_kill_sound(void);
t_process	*vm_fork(t_vm *vm, t_champ *champ, t_vptr offset);
void		vm_kill(t_vm *vm, t_byte cid, t_process *pc);
void		dump(t_vm *vm);

#endif