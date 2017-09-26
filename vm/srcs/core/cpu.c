/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:29:43 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 10:06:13 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	g_op_tab[OP_NBR] =
{
	{"live", 1, ARG_LIVE, 1, {0}, 10, "alive", 0, 0, &inst_live, 0},
	{"ld", 2, ARG_LD, 2, {0}, 5, "load", 1, 0, &inst_ld, 0},
	{"st", 2, ARG_ST, 3, {0}, 5, "store", 1, 0, &inst_st, 0},
	{"add", 3, ARG_ADD, 4, {0}, 10, "add", 1, 0, &inst_add, 0},
	{"sub", 3, ARG_SUB, 5, {0}, 10, "sub", 1, 0, &inst_sub, 0},
	{"and", 3, ARG_AND, 6, {0}, 6, "and", 1, 0, &inst_and, 0},
	{"or", 3, ARG_OR, 7, {0}, 6, "or", 1, 0, &inst_or, 0},
	{"xor", 3, ARG_XOR, 8, {0}, 6, "xor", 1, 0, &inst_xor, 0},
	{"zjmp", 1, ARG_ZJMP, 9, {0}, 20, "jump", 0, 1, &inst_zjmp, 0},
	{"ldi", 3, ARG_LDI, 10, {0}, 25, "load i", 1, 1, &inst_ldi, 0},
	{"sti", 3, ARG_STI, 11, {0}, 25, "store i", 1, 1, &inst_sti, 0},
	{"fork", 1, ARG_FORK, 12, {0}, 800, "fork", 0, 1, &inst_fork, 0},
	{"lld", 2, ARG_LLD, 13, {0}, 10, "l load", 1, 0, &inst_lld, 0},
	{"lldi", 3, ARG_LLDI, 14, {0}, 50, "ll index", 1, 1, &inst_lldi, 0},
	{"lfork", 1, ARG_LFORK, 15, {0}, 1000, "long fork", 0, 1, &inst_lfork, 0},
	{"aff", 1, ARG_AFF, 16, {0}, 2, "aff", 1, 0, &inst_aff, 0},
};

void		exec(t_vm *vm, t_byte ci, t_process *pc)
{
	if (!OPVALIDE(pc->inst[0]))
		return ;
	if (params_load(vm, pc))
	{
		pc->zc = pc->pc;
		if (vm->params->verbose & PV_OPS && vm->inst_loaded)
			(vm->inst_loaded)(&vm->champs[ci], pc);
		(g_op_tab[pc->inst[0] - 1].call)(vm, ci, pc);
	}
	pc->zc = pc->pc;
	if (vm->pc_updated)
		(vm->pc_updated)(pc);
}

void		cpu_pc_process(t_vm *vm, int ci, t_process *pc)
{
	if (!(pc->flags & PF_WAIT))
	{
		pc->pc = ABSPTR(pc->pc);
		ft_bzero(pc->inst, sizeof(t_int32) * 6);
		pc->cc = pc->pc;
		pc->inst[0] = mem_readbyte(&vm->memory, pc->pc++);
		if (OPVALIDE(pc->inst[0]))
		{
			pc->flags |= PF_WAIT;
			pc->cycles_to_do = g_op_tab[pc->inst[0] - 1].nbr_cycles;
		}
	}
	if (pc->cycles_to_do-- <= 1)
	{
		exec(vm, ci, pc);
		pc->flags &= ~PF_WAIT;
	}
}

void		cpu_champ_process_pc(t_vm *vm)
{
	t_process	*pc;

	pc = vm->process;
	while (pc)
	{
		cpu_pc_process(vm, pc->champ_index, pc);
		pc->last_live++;
		pc = pc->next;
	}
}

void		cpu_process_cycle(t_vm *vm)
{
	cpu_champ_process_pc(vm);
	if (vm->params->flag & P_DUMP && --vm->params->dump <= 0)
		dump(vm);
}
