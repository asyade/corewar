/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:29:43 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 04:03:30 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op    op_tab[OP_NBR] =
{
	//name		?	params									ID	Cycles			describ	 OCP? 2/4 CallBack  Already used
	{"live",	1, (t_arg_type[]){FT_DIR, 0, 0, 0 }, 					1, {0},	10,			"alive",	0, 0, &inst_live, 0 },
	{"ld",		2, (t_arg_type[]){FT_DIR | FT_IND, FT_REG, 0, 0 },	2, {0},	5,			"load",		1, 0, &inst_ld, 0 },
	{"st",		2, (t_arg_type[]){FT_REG, FT_IND | FT_REG, 0 ,0},	3, {0},	5,			"store",	1, 0, &inst_st, 0 },
	{"add",		3, (t_arg_type[]){FT_REG, FT_REG, FT_REG, 0 }, 	4, {0},	10,			"add",		1, 0, &inst_add, 0 },
	{"sub",		3, (t_arg_type[]){FT_REG, FT_REG, FT_REG, 0 }, 	5, {0},	10,			"sub", 		1, 0, &inst_sub, 0 },
	{"and",		3, (t_arg_type[]){FT_REG | FT_DIR | FT_IND, FT_REG | FT_IND | FT_DIR, FT_REG, 0},
															6, {0},	6,			"and",		1, 0, &inst_and, 0 },
	{"or",		3, (t_arg_type[]){FT_REG | FT_DIR | FT_IND, FT_REG | FT_IND | FT_DIR, FT_REG, 0},
															7, {0},	6,			"or",		1, 0, &inst_or, 0 },
	{"xor",		3, (t_arg_type[]){FT_REG | FT_DIR | FT_IND, FT_REG | FT_IND | FT_DIR, FT_REG, 0},
															8, {0},	6,			"xor",		1, 0, &inst_xor, 0 },
	{"zjmp",	1, (t_arg_type[]){FT_DIR, 0, 0, 0},					9, {0},	20,			"jump", 	0, 1, &inst_zjmp, 0 },
	{"ldi", 	3, (t_arg_type[]){FT_REG | FT_DIR | FT_IND, FT_DIR | FT_REG, FT_REG, 0},
															10, {0},	25,		"load i",	1, 1, &inst_ldi, 0 },
	{"sti", 	3, (t_arg_type[]){FT_REG, FT_REG | FT_DIR | FT_IND, FT_DIR | FT_REG, 0},
															11, {0},	25,		"store i",	1, 1, &inst_sti, 0 },
	{"fork", 	1, (t_arg_type[]){FT_DIR, 0, 0, 0},					12, {0},	800,	"fork",		0, 1, &inst_fork, 0 },
	{"lld", 	2, (t_arg_type[]){FT_DIR | FT_IND, FT_REG, 0, 0}, 13, {0},	10, 	"l load",	1, 0, &inst_lld, 0 },
	{"lldi", 	3, (t_arg_type[]){FT_REG | FT_DIR | FT_IND, FT_DIR | FT_REG, FT_REG, 0},
															14, {0},	50,		"ll index", 1, 1, &inst_lldi, 0 },
	{"lfork", 	1, (t_arg_type[]){FT_DIR, 0, 0, 0},					15, {0},	1000,	"long fork",0, 1, &inst_lfork, 0 },
	{"aff", 	1, (t_arg_type[]){FT_REG, 0, 0, 0},					16, {0},	2,		"aff",		1, 0, &inst_aff, 0 },
};

void		exec(t_vm *vm, t_byte ci, t_process *pc)
{
	if (!OPVALIDE(pc->inst[0]))
		return ;
	if (params_load(vm, pc))
	{
		pc->zc = pc->pc;
		if (vm->params->verbose & PV_OPS && vm->instLoaded)
			(vm->instLoaded)(&vm->champs[ci], pc);
		(op_tab[pc->inst[0] - 1].call)(vm, ci, pc);
	}
	pc->zc = pc->pc;
	if (vm->pcUpdated)
		(vm->pcUpdated)(pc);
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
			pc->cycles_to_do = op_tab[pc->inst[0] - 1].nbr_cycles;
		}
	}
	if (pc->cycles_to_do-- <= 1)
	{
		exec(vm, ci, pc);
		pc->flags &= ~PF_WAIT;
	}
}

void		cpu_champ_process_pc(t_vm *vm, int ci, t_champ *ch)
{
	t_process	*pc;

	(void)ci;
	(void)ch;
	pc = vm->process;
	while (pc)
	{
		pc->last_live++;
		cpu_pc_process(vm, pc->champ_index, pc);
		pc = pc->next;
	}
}

void		cpu_process_cycle(t_vm *vm)
{
	int 		ci;

	ci = -1;
//	while (++ci < vm->champ_count)
//	{
		cpu_champ_process_pc(vm, ci, &vm->champs[ci]);
//	}
	if (vm->params->flag & P_DUMP && --vm->params->dump <= 0)
		dump(vm);
}
