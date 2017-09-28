/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shenv_verbose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 13:56:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 23:30:05 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_sh.h"

void			cb_cycle_updated(void)
{
	static long long int	total = 0;
	t_vm					*vm;

	vm = &sh_env(NULL)->vm;
	total++;
	if (vm->params->verbdellay != -1 && --vm->params->verbdellay > 0)
		return ;
	if (!(vm->params->verbose & PV_CYCLES))
		return ;
	ft_printf("It is now cycle %lld\n", total);
}

void			cb_pc_updated(t_process *pc)
{
	char			buffer[1024 * 4 * 8];
	char			*ptr;
	t_vptr			i;
	t_memory		*mem;

	if (!(sh_env(NULL)->vm.params->verbose & PV_MOVES) ||
(pc->inst[0] == 9 && pc->flags & PF_CARRY))
		return ;
	mem = &sh_env(NULL)->vm.memory;
	i = pc->cc;
	ptr = buffer;
	if (labs(pc->zc - i) > 500)
		return ;
	while (i < pc->zc)
	{
		*ptr++ = BASE_HEX_MAJ[mem_readbyte(mem, i) / 16];
		*ptr++ = BASE_HEX_MAJ[mem_readbyte(mem, i++) % 16];
		*ptr++ = ' ';
	}
	*ptr = '\0';
	ft_printf("ADV %ld (0x%x -> 0x%x) %s\n",
pc->zc - pc->cc, pc->cc, pc->zc, buffer);
}

char			*carry_label(t_process *pc)
{
	static char	buff[1024];

	if (pc->inst[0] == 9)
		return (pc->flags & PF_CARRY) ? " OK" : " FAILED";
	if (pc->inst[0] == 12 || pc->inst[0] == 15)
	{
		buff[0] = '\0';
		ft_sprintf(buff, " (%ld)", (pc->inst[0] == 15) ?
pc->cc + pc->inst[1] : IDXPTR(pc->cc, pc->inst[1]));
		return (buff);
	}
	return ("");
}

void			dump_inst_called(void)
{
	int			i;

	i = -1;
	ft_putendl("the following instructions have been used :\n");
	while (++i < OP_NBR)
	{
		if (g_op_tab[i].called)
		{
			ft_putendl(g_op_tab[i].name);
		}
	}
}

void			cb_inst_loaded(t_champ *c, t_process *p)
{
	(void)c;
	if (p->inst[0] == 16)
		return ;
	ft_printf("P %d | %s%s%s\n", p->id,
g_op_tab[p->inst[0] - 1].name,
dump_parametters(&sh_env(NULL)->vm, p, inst_count(p->inst[0])),
carry_label(p));
	if (p->inst[0] == 11)
	{
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %ld)\n",
			param_dirval(p, 2),
			param_dirval(p, 3),
			param_dirval(p, 2) + param_dirval(p, 3),
			p->cc + param_dirval(p, 2) + param_dirval(p, 3));
	}
	else if (p->inst[0] == 10)
	{
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %ld)\n",
			param_dirval(p, 1), param_dirval(p, 2),
			param_dirval(p, 1) + param_dirval(p, 2),
			IDXPTR(p->cc, param_dirval(p, 1) + param_dirval(p, 2)));
	}
}
