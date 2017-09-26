/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 10:03:39 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_core		*core_init(void)
{
	t_core	*core;

	core = ft_salloc(sizeof(t_core));
	ft_bzero(core, sizeof(t_core));
	vm_init(&(core->vm));
	return (core);
}

void		core_load_callback(t_core *core)
{
	core->vm.mem_updated = core->render.mem_updated;
	core->vm.process_loaded = core->render.process_loaded;
	core->vm.cycle_updated = core->render.cycle_updated;
	core->vm.process_die = core->render.process_die;
	core->vm.player_live = core->render.player_live;
	core->vm.player_die = core->render.player_die;
	core->vm.inst_loaded = core->render.inst_loaded;
	core->vm.pc_updated = core->render.pc_updated;
}
