/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:33 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/30 03:16:05 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_init(t_vm *vm)
{
	int		i;

	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->total_process = 0;
	vm->process = NULL;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->champs[i].flags = PC_NONE;
	}
}

void			vm_load_champ(t_vm *vm, t_champ *champ, t_vptr offset)
{
	mem_write(vm, champ->body,
				(t_memzone){champ->header.size, offset}, champ->index);
	champ->flags = PC_LOADED;
}

inline t_process		*vm_fork(t_vm *vm, t_champ *champ, t_vptr offset)
{
	t_process	*npc;

	if (!(champ->flags & PC_LOADED))
		return (NULL);
	vm->alive_process++;
	npc = pc_new(champ->number);
	npc->pc = offset;
	pc_push(&vm->process, npc);
	npc->id = ++vm->total_process;
	if (vm->process_loaded)
		vm->process_loaded(champ);
	npc->flags = 0;
	return (npc);
}

inline void			vm_kill(t_vm *vm, t_process *pc, t_process *prev)
{
	t_process	*next;

	next = pc->next;
	vm->alive_process--;
	free(pc);
	if (!prev)
		vm->process = next;
	else
		prev->next = next;
	if (vm->params->flag & P_SOUND)
		vm_kill_sound();
}
