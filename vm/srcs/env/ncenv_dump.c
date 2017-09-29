/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncenv_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 05:39:53 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_ncurse.h"

void		nc_dump(WINDOW *win, t_memory *mem)
{
	t_vptr		ptr;
	int			y;
	int			x;

	ptr = 0;
	y = 1;
	wattron(win, COLOR_PAIR(0));
	if (COLS < NC_COLS_MIN || LINES < NC_LINES_MIN)
		return ;
	while (ptr < MEM_SIZE && y <= 63)
	{
		x = 0;
		while (++x < (NC_MEMWIN_WIDTH + 4) / 3 && ptr < MEM_SIZE)
		{
			wattron(win, nc_color_mem(mem->trace[ptr]));
			wmove(win, y, x * 3);
			waddch(win, (char)BHEX[mem->mem[ptr] / 16]);
			waddch(win, (char)BHEX[mem->mem[ptr] % 16]);
			wattroff(win, nc_color_mem(mem->trace[ptr]));
			ptr++;
		}
		y++;
	}
}

void		nc_dump_limits(int x, int y, int offset, int size)
{
	t_core	*c;
	WINDOW	*w;
	t_byte	b;

	w = nc_mem_win();
	c = nc_env(NULL);
	if (COLS < NC_COLS_MIN || LINES < NC_LINES_MIN)
		return ;
	while (size-- > 0)
	{
		b = mem_readbyte(&c->vm.memory, offset);
		wmove(w, y, x + 3);
		wattron(w, nc_color_mem(c->vm.memory.trace[offset]));
		waddch(w, BHEX[b / 16]);
		waddch(w, BHEX[b % 16]);
		wattroff(w, nc_color_mem(c->vm.memory.trace[offset]));
		x += 3;
		if (x >= NC_MEMWIN_WIDTH)
		{
			x = 0;
			y = (y < 64) ? y + 1 : 1;
		}
		offset++;
	}
}
