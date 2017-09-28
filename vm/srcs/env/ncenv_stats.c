/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncenv_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/28 20:32:54 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_ncurse.h"

void		nc_dump_champ_name(WINDOW *win, t_core *core)
{
	int		i;
	int		y;

	i = -1;
	y = 9;
	while (++i < core->vm.champ_count)
	{
		wmove(win, y, 2);
		core->vm.champs[i].header.name[36] = '\0';
		wattron(win, COLOR_PAIR(i + 1) | A_DIM);
		wprintw(win, core->vm.champs[i].header.name);
		wattroff(win, COLOR_PAIR(i + 1));
		y += 3;
	}
}

void		nc_dump_champ_infos(WINDOW *win, t_core *core)
{
	char	buff[1024];
	int		i;
	int		y;

	(void)win;
	(void)core;
	y = 10;
	i = -1;
	while (++i < core->vm.champ_count)
	{
		sprintf(buff, "Lives in current periode %d     ",
					core->vm.champs[i].nbr_live);
		wmove(win, y, 3);
		wprintw(win, buff);
		y += 3;
	}
}

void		nc_dump_basic(WINDOW *win, t_core *core, int st, int dellay)
{
	char	buffer[1024];

	(void)core;
	wattron(win, COLOR_PAIR(0));
	wmove(win, 2, 2);
	sprintf(buffer, "%s - Interval %d ms                ",
		(!st) ? "** PAUSED **" : "** RUNNING **", dellay);
	buffer[36] = '\0';
	wprintw(win, buffer);
	wmove(win, 4, 2);
	buffer[0] = '\0';
	sprintf(buffer, "Processes %d", core->vm.total_process);
	wprintw(win, buffer);
}

void		nc_dump_cycle(WINDOW *win, long int cycle)
{
	char	buffer[1024];

	sprintf(buffer, "Cycle %ld", cycle);
	wmove(win, 5, 2);
	wprintw(win, buffer);
	wmove(win, 6, 2);
	buffer[0] = '\0';
	sprintf(buffer, "Cycle to die %d     ", nc_env(NULL)->vm.cycles_to_die);
	wprintw(win, buffer);
	nc_dump_champ_infos(win, nc_env(NULL));
}
