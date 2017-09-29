/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ncurse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 06:25:45 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_NCURSE_H
# define ENV_NCURSE_H

# include "corewar.h"
# include <ncurses.h>

# define BHEX				"0123456789abcdef"

# define NC_MEMWIN_X			0
# define NC_MEMWIN_Y			0
# define NC_MEMWIN_WIDTH		(64 * 3)
# define NC_MEMWIN_HEIGHT		(64)
# define NC_COLS_MIN		(NC_MEMWIN_WIDTH + 40)
# define NC_LINES_MIN		(NC_MEMWIN_HEIGHT)

# define NC_STWIN_Y			0
# define NC_STWIN_X			NC_MEMWIN_WIDTH + 4
# define NC_STWIN_WIDTH		40
# define NC_STWIN_HEIGHT		64

# define NCF_RUNNING			1
# define NCF_PAUSED			0

# define NC_CYCLE_DELLAY		0
# define NC_CYCLE_DELLAY_DEL	10

void		nc_init_colors();
int			nc_color_mem(int trace);

WINDOW		*nc_mem_win(void);
WINDOW		*nc_st_win(void);
void		nc_stwin_refresh(void);
void		nc_memwin_refresh(void);

t_core		*nc_env(t_core *c);
void		nc_key_hook(void);

void		cb_envdone(t_vm *vm);
void		nc_end(void);
void		nc_dump(WINDOW *win, t_memory *mem);
void		nc_dump_limits(int x, int y, int offset, int size);
void		nc_dump_basic(WINDOW *win, t_core *core, int st, int dellay);
void		nc_dump_champ_name(WINDOW *win, t_core *core);
void		nc_dump_cycle(WINDOW *win, long int cycle);
void		nce_init(t_core *core);

#endif
