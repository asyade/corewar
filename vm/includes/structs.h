/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:44:33 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 03:03:43 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define PF_NONE		(0)
# define PF_LIVEUP		(1 << 1)
# define PF_WAIT		(1 << 2)
# define PF_CARRY		(1 << 3)

# define PC_ALIVE		(1 << 24)
# define PC_LOADED		(1 << 5)
# define PC_DEAD		(1 << 6)
# define PC_NONE		(1 << 7)
# define PC_DIE			(1 << 8)
# define PC_YOUNG		(1 << 9)

# define P_VERBOSE		(1 << 1)
# define P_NCURSE		(1 << 2)
# define P_SH			(1 << 3)
# define P_DUMP			(1 << 4)
# define P_DUMPREP		(1 << 5)
# define P_SOUND		(1 << 6)
# define P_SHOWAFF		(1 << 7)

# define PV_ESSENTAL	(0)
# define PV_LIVES		(1 << 0)
# define PV_CYCLES		(1 << 1)
# define PV_OPS			(1 << 2)
# define PV_DEATH		(1 << 3)
# define PV_MOVES		(1 << 4)
# define PV_DMPINST		(1 << 5)

typedef struct			s_champ_describ
{
	char				*path;
	int					index;
	int					number;
}						t_champ_describ;

typedef struct			s_memzone
{
	t_vsize				size;
	t_vptr				offset;
}						t_memzone;

typedef struct			s_param
{
	t_int32				flag;
	t_int32				verbose;
	t_int32				dump;
	t_int32				basedump;
	t_int32				count;
	t_int32				verbdellay;
	t_champ_describ		champs[4];
}						t_param;

typedef	struct			s_process
{
	int					id;
	t_int64				last_live;
	t_reg				reg[REG_NUMBER];
	t_vptr				pc;
	t_vptr				cc;
	t_vptr				zc;
	t_int32				inst[6];
	t_flags				flags;
	t_int32				cycles_to_do;
	t_int32				champ_index;
	struct s_process	*next;
}						t_process;

typedef struct			s_champ_header
{
	t_uint32			magic;
	t_char				name[PROG_NAME_LEN + 1];
	t_vsize				size;
	t_char				comment[COMMENT_LEN + 1];
}						t_champ_header;

typedef	struct			s_champ
{
	t_champ_header		header;
	t_byte				*body;
	t_int32				nbr_process;
	t_byte				number;
	t_int32				index;
	t_flags				flags;
	uint32_t			nbr_live;
}						t_champ;

typedef	struct			s_memory
{
	t_byte				mem[MEM_SIZE];
	t_byte				trace[MEM_SIZE];
}						t_memory;

typedef struct			s_vm
{
	t_process			*process;
	t_param				*params;
	void				(*cycle_updated)(void);
	void				(*mem_updated)(t_memory *, int, int);
	void				(*process_loaded)(t_champ *c);
	void				(*process_die)(t_champ *, t_process *);
	void				(*player_live)(t_champ *c, int);
	void				(*player_die)(t_champ *c);
	void				(*live_delta)(int);
	void				(*inst_loaded)(t_champ *, t_process *);
	void				(*pc_updated)(t_process *pc);
	t_memory			memory;
	t_champ				champs[MAX_PLAYERS];
	t_byte				champ_count;
	t_int32				cycles_to_die;
	t_int32				total_process;
	t_int32				cycles;
	t_int32				lives;
	t_int32				nbr_check;
	int					winner;
}						t_vm;

/*
** Callback
*/

typedef void			(*t_lives_delta)(int);
typedef void			(*t_process_die)(t_champ *, t_process *);
typedef void			(*t_player_die)(t_champ *);
typedef void			(*t_player_win)(t_champ *);

/*
** t_champ		sender
** int			live parametter
*/

typedef void			(*t_player_live)(t_champ *, int);
typedef void			(*t_process_loaded)(t_champ *);
typedef void			(*t_inst_loaded)(t_champ *c, t_process *pc);
typedef void			(*t_pc_updated)(t_process *pc);

/*
**	t_memory * 	memory
**	int			offset
**	int			size (octe)
*/

typedef void			(*t_mem_updated)(t_memory *, int, int);
typedef int				(*t_load_champs)(void);
typedef	void			(*t_cycle_updated)(void);
typedef void			(*t_env_done)(t_vm *vm);
typedef void			(*t_cycle_delta)(int ctd);

/*
** Public
*/

typedef struct			s_render
{
	t_cycle_updated		cycle_updated;
	t_cycle_delta		cycle_delta;
	t_lives_delta		lives_delta;
	t_process_die		process_die;
	t_player_win		player_win;
	t_player_die		player_die;
	t_player_live		player_live;
	t_process_loaded	process_loaded;
	t_mem_updated		mem_updated;
	t_env_done			env_done;
	t_inst_loaded		inst_loaded;
	t_pc_updated		pc_updated;
}						t_render;

typedef struct			s_core
{
	t_load_champs		load_champs;
	t_render			render;
	t_vm				vm;
}						t_core;

#endif
