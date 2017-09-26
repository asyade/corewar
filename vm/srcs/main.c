/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 07:09:35 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"
# include "source.h"
# include "envNcurse.h"
# include "envSh.h"
# include "sdlenv.h"

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

int		main(t_int32 ac, t_char **av)
{
	t_core	*core;
	t_param	*p;

	if (!(p = read_params(ac - 1, av + 1)))
		usage();
	core = core_init();
	loadChampsDefault(p, core);
	core->vm.params = p;
	load_env(core, p);
	core_load_callback(core);
	if (core->vm.champ_count <= 0)
	{
		usage();
		return (1);
	}
	core->vm.winner = play(core);
	core->vm.memory.mem[0] = 0xff;
	core->vm.memUpdated(&core->vm.memory, 0, 0);

	if (core->render.envDone)
		(core->render.envDone)(&core->vm);
	int	i;
	i = -1;
	while (++i < core->vm.champ_count)
	{
		free(core->vm.champs[i].body);
	}
	pc_clear(core->vm.process);
	free(core);
}
