/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/14 20:31:12 by acorbeau         ###   ########.fr       */
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

void	usage(void)
{
	ft_putendl("./corewar [-dump cycle] [prog_name]...");
	exit(1);
}

void	load_env(char *name, t_core *core)
{
	if (!name)
		she_init(core);
	else if (ft_strequ(name, "nc"))
		nce_init(core);
	else if (ft_strequ(name, "sdl"))
		sdle_init(core);
	//TODO env default
}

int		main(t_int32 ac, t_char **av)
{
	t_core	*core;

	core = core_init();
	loadChampsDefault(ac - 1, av + 1, core);
	load_env(getenv("env"), core);
	core_load_callback(core);
	if (core->vm.champ_count <= 0)
	{
		usage();
		return (1);
	}
	play(core);
	core->vm.memory.mem[0] = 0xff;
        core->vm.memUpdated(&core->vm.memory, 0, 0);

}
