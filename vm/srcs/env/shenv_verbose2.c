/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shenv_verbose2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 13:56:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:39:04 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_sh.h"

void			cb_pc_die(t_champ *champ, t_process *pc)
{
	(void)champ;
	if (params()->verbose & PV_DEATH)
		printf("Process %d hasn't lived for %ld cycles (CTD %d)\n",
pc->id, pc->last_live, sh_env(NULL)->vm.cycles_to_die);
}

void			cb_player_die(t_champ *champ)
{
	plog("%s: Die\n", champ->header.name);
}

void			cb_player_live(t_champ *c, int id)
{
	if (!(params()->verbose & PV_LIVES))
		return ;
	if (-id == c->number)
		printf("Player %d (%s) is said to be alive\n",
c->number, c->header.name);
}

void			cb_envdone(t_vm *vm)
{
	t_champ		*ch;
	int			i;

	if (vm->params->verbose & PV_DMPINST)
		dump_inst_called();
	ch = &vm->champs[vm->winner];
	i = -1;
	while (++i < vm->champ_count)
	{
		if (vm->champs[i].flags & PC_ALIVE)
			ch = &vm->champs[i];
	}
	printf("Contestant %d, \"%s\", has won !\n",
ch->number, ch->header.name);
}

void			cb_cycle_to_die_delta(int ctd)
{
	if (sh_env(NULL)->vm.params->verbose & PV_CYCLES)
		printf("Cycle to die is now %d\n", ctd);
}
