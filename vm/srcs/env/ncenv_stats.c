/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncenv_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/30 04:06:29 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_ncurse.h"

inline void		nc_dump_champ_name(WINDOW *win, t_core *core)
{
	int		i;
	int		y;

	i = -1;
	y = 9;
	if (COLS < NC_COLS_MIN || LINES < NC_LINES_MIN)
		return ;
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

void			nc_dump_champ_infos(WINDOW *win, t_core *core)
{
	char	buff[1024];
	int		i;
	int		y;

	if (COLS < NC_COLS_MIN || LINES < NC_LINES_MIN)
		return ;
	y = 10;
	i = -1;
	while (++i < core->vm.champ_count)
	{
		ft_sprintf(buff, "Lives in current periode %d     ",
					core->vm.champs[i].nbr_live);
		wmove(win, y, 3);
		wprintw(win, buff);
		y += 3;
	}
}

inline void		nc_dump_basic(WINDOW *win, t_core *core, int st, int dellay)
{
	char	buffer[1024];

	if (COLS < NC_COLS_MIN || LINES < NC_LINES_MIN)
		return ;
	wattron(win, COLOR_PAIR(0));
	wmove(win, 2, 2);
	ft_sprintf(buffer, "%s - Interval %d ms                ",
		(!st) ? "** PAUSED **" : "** RUNNING **", dellay);
	buffer[36] = '\0';
	wprintw(win, buffer);
	wmove(win, 4, 2);
	buffer[0] = '\0';
	ft_sprintf(buffer, "Processes %d", core->vm.alive_process);
	wprintw(win, buffer);
}

inline void		nc_dump_cycle(WINDOW *win, long int cycle)
{
	char	buffer[1024];

	if (COLS < NC_COLS_MIN || LINES < NC_LINES_MIN)
		return ;
	ft_sprintf(buffer, "Cycle %ld", cycle);
	wmove(win, 5, 2);
	wprintw(win, buffer);
	wmove(win, 6, 2);
	buffer[0] = '\0';
	ft_sprintf(buffer, "Cycle to die %d     ", nc_env(NULL)->vm.cycles_to_die);
	wprintw(win, buffer);
	nc_dump_champ_infos(win, nc_env(NULL));
	nc_memwin_refresh();
}
