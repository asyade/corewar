/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:33 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/10 02:10:25 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_init(t_vm *vm)
{
	int		i;

	vm->cycles_to_die = CYCLE_TO_DIE;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->champs[i].flags = PC_NONE;
	}
}

void		vm_load_champ(t_vm *vm, t_champ *champ, t_vptr offset)
{
	mem_write(vm, champ->body, champ->header.size, offset, champ->number);
	champ->flags |= PC_LOADED;
}

/*
** Gestion des process pouris, a revoir surment une liste doublement chainée mais la fléme tout de suite
*/

t_process		*vm_fork(t_vm *vm, t_champ *champ, t_vptr offset)
{
	t_process	*npc;

	if (!(champ->flags & PC_LOADED))
	{
		pcri("%s: Can't fork, champion not initialized !");
		return (NULL);
	}
	npc = pc_new(champ->number);
	npc->pc = offset;
	pc_push(&champ->process, npc);
	champ->nbr_process++;
	if (vm->processLoaded)
		vm->processLoaded(champ);
	return (npc);
}



void		vm_kill(t_vm *vm, t_byte cid, t_process *pc)
{
	vm->champs[cid].nbr_process--;
	pc_remove(&vm->champs[cid].process, pc);
	if (vm->params->flag & P_SOUND)
		vm_kill_sound();
}