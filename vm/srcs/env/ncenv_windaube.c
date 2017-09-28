/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncenv_windaube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/28 23:18:23 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_ncurse.h"

WINDOW		*nc_mem_win(void)
{
	static WINDOW		*win = NULL;

	if (win == NULL)
	{
		win = newwin(
			NC_MEMWIN_HEIGHT + 1,
			NC_MEMWIN_WIDTH + 4,
			0, 0);
	}
	return (win);
}

WINDOW		*nc_st_win(void)
{
	static WINDOW		*win = NULL;

	if (win == NULL)
	{
		win = newwin(
			NC_STWIN_HEIGHT + 1,
			NC_STWIN_WIDTH + 4,
			NC_STWIN_Y, NC_STWIN_X);
	}
	return (win);
}

void		nc_memwin_refresh(void)
{
	WINDOW		*win;

	win = nc_mem_win();
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(win);
	win = nc_st_win();
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(win);
}

void		nc_end(void)
{
	nodelay(stdscr, 0);
	getch();
	endwin();
	free(nc_mem_win());
	free(nc_st_win());
}
