/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:29:43 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/14 05:16:23 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		exec(t_vm *vm, t_byte ci, t_process *pc)
{
	int				success;
	static t_inst	inst_table[] = {
		&inst_live,
		&inst_ld,
		&inst_st,
		&inst_add,
		&inst_sub,
		&inst_and,
		&inst_or,
		&inst_xor,
		&inst_zjmp,
		&inst_ldi,
		&inst_sti,
		&inst_fork,
		&inst_lld,
		&inst_lldi,
		&inst_lfork,
		&inst_aff
	};

	if (!OPVALIDE(pc->inst[0]))
		return ;
	params_load(vm, pc);

	if (!(success = (inst_table[pc->inst[0] - 1])(vm, ci, pc)))
		update_invalide_pc(pc);
	if (vm->params->verbose & PV_OPS && vm->instLoaded)
		(vm->instLoaded)(&vm->champs[ci], pc);
	if (vm->pcUpdated)
		(vm->pcUpdated)(pc);
}

t_int32		exec_dellay(t_byte  opcode)
{
	static t_int32	dellay_table[] = {
		10,
		5,
		5,
		10,
		10,
		6,
		6,
		6,
		20,
		25,
		25,
		800,
		10,
		50,
		1000,
		2
	};

	if (!(OPVALIDE(opcode)))
		return (0);
	return (dellay_table[opcode - 1]);
}

void		cpu_do_ops(t_vm *vm, int ci, t_champ *ch)
{
	t_process	*pc;

	pc = ch->process;
	while (pc)
	{
		if (!(pc->flags & PF_WAIT))
		{
			ft_bzero(pc->inst, sizeof(t_int32) * 6);
			pc->cc = pc->pc++;
			pc->inst[0] = vm->memory.mem[ABSPTR(pc->cc)];
			pc->flags |= PF_WAIT;
			pc->cycles_to_do = exec_dellay(pc->inst[0]);
		}
		if (--pc->cycles_to_do <= 0)
		{
			exec(vm, ci, pc);
			pc->flags &= ~PF_WAIT;
		}
		pc = pc->next;
	}
}

void		cpu_process_cycle(t_vm *vm)
{
	int 		ci;

	ci = -1;
	while (++ci < vm->champ_count)
	{
		cpu_do_ops(vm, ci, &vm->champs[ci]);
	}
	if (vm->params->flag & P_DUMP && vm->params->dump-- <= 0)
		dump(vm);
	if (vm->cycleUpdated)
		(vm->cycleUpdated)();
}