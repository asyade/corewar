/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 13:56:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:38:28 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_sh.h"

t_core			*sh_env(t_core *c)
{
	static	t_core	*core;

	if (c)
		core = c;
	return (core);
}

void			show_consts(t_core *c)
{
	int			i;

	printf("Introducing contestants...\n");
	i = -1;
	while (++i < c->vm.champ_count)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
c->vm.champs[i].header.size,
c->vm.champs[i].header.name, c->vm.champs[i].header.comment);
	}
}

int				inst_count(int opcode)
{
	static int	pcount[16] = { 0, 2, 2, 3, 3, 3, 3, 3, 0, 3, 3, 0, 2, 3, 0, 0 };

	return (OPVALIDE(opcode)) ? (pcount[opcode - 1]) : -1;
}

void			she_init(t_core *core)
{
	sh_env(core);
	show_consts(core);
	core->render.cycle_delta = &cb_cycle_to_die_delta;
	core->render.inst_loaded = &cb_inst_loaded;
	core->render.cycle_updated = &cb_cycle_updated;
	core->render.env_done = &cb_envdone;
	core->render.player_live = &cb_player_live;
	core->render.lives_delta = &cb_live_delta;
	core->render.process_die = &cb_pc_die;
	core->render.player_die = &cb_player_die;
	core->render.process_loaded = &cb_pc_loaded;
	core->render.pc_updated = &cb_pc_updated;
	core->render.mem_updated = cb_mem_updated;
}
