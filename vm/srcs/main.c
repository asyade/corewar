/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 01:54:13 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "env_ncurse.h"
#include "env_sh.h"

/*
** Corewar vm - acorbeau
*/

void	load_env(t_core *core, t_param *p)
{
	if (p->flag & P_NCURSE)
		nce_init(core);
	else
		she_init(core);
}

void	run_core(t_core *core)
{
	int	i;

	core->vm.winner = play(core);
	core->vm.memory.mem[0] = 0xff;
	core->vm.mem_updated(&core->vm.memory, 0, 0);
	if (core->render.env_done)
		(core->render.env_done)(&core->vm);
	i = -1;
	while (++i < core->vm.champ_count)
	{
		free(core->vm.champs[i].body);
	}
	pc_clear(core->vm.process);
	free(core);
}

int		main(t_int32 ac, t_char **av)
{
	t_core	*core;
	t_param	*p;

	if (!(p = read_params(ac - 1, av + 1)))
		usage();
	core = core_init();
	core->vm.params = p;
	load_champs_default(p, core);
	load_env(core, p);
	core_load_callback(core);
	if (core->vm.champ_count <= 0)
		usage();
	else
		run_core(core);
	if (p->flag & P_NCURSE)
		nc_end();
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
}
