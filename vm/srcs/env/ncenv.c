/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:44:33 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/28 23:18:07 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_ncurse.h"

t_core		*nc_env(t_core *c)
{
	static t_core		*singelton = NULL;

	if (c)
		singelton = c;
	return (singelton);
}

void		nc_cb_mem_updated(t_memory *mem, int a, int b)
{
	int		x;
	int		xrel;
	int		y;

	(void)mem;
	y = a / 64;
	x = a - (y * 64);
	xrel = (x * 2) + x;
	nc_dump_limits(xrel, y, a, b);
	nc_memwin_refresh();
}

void		nc_cb_cycle_updated(void)
{
	static int			dumped = 0;
	static long int		cycle = 1;

	if (!dumped)
	{
		nc_dump(nc_mem_win(), &nc_env(NULL)->vm.memory);
		dumped = 1;
	}
	nc_dump_cycle(nc_st_win(), cycle++);
	nc_key_hook();
}

void		nc_key_hook(void)
{
	static int		dellay = NC_CYCLE_DELLAY;
	static int		stat = NCF_PAUSED;
	char			c;

	if (stat == NCF_PAUSED)
		nc_dump_basic(nc_st_win(), nc_env(NULL), stat, dellay);
	while (stat == NCF_PAUSED)
	{
		nc_memwin_refresh();
		if (getch() == ' ')
			stat = NCF_RUNNING;
	}
	c = getch();
	if (c == ' ')
		stat = NCF_PAUSED;
	else if (c == '+')
		dellay += NC_CYCLE_DELLAY_DEL;
	else if (c == '-')
		dellay += NC_CYCLE_DELLAY_DEL;
	else if (c == 'r')
		dellay = NC_CYCLE_DELLAY;
	nc_dump_basic(nc_st_win(), nc_env(NULL), stat, dellay);
	(dellay >= 0) ? usleep(dellay) : 0;
}

void		nce_init(t_core *c)
{
	nc_env(c);
	c->render.mem_updated = &nc_cb_mem_updated;
	c->render.cycle_updated = &nc_cb_cycle_updated;
	initscr();
	nc_init_colors();
	nodelay(stdscr, TRUE);
	nc_mem_win();
	nc_dump_champ_name(nc_st_win(), c);
}
