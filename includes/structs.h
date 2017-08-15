/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:44:33 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/15 01:31:09 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define PF_NONE	0x00
# define PF_LIVEUP	0x08
# define PF_WAIT	0x04
# define PF_CARRY	0x02

# define PC_ALIVE	0x80
# define PC_LOADED	0x40
# define PC_DEAD	0x20
# define PC_NONE	0x10

typedef	struct			s_process
{
	t_reg				reg[REG_NUMBER];
	t_vptr				pc;
	t_vptr				cc;
	t_int32				inst[6];
	t_flags				flags;
	t_int32				cycles_to_do;
	struct s_process	*next;
}						t_process;

typedef struct			s_champHeader
{
	t_uint32			magic;
	t_char				name[PROG_NAME_LEN + 1];
	t_vsize				size;
	t_char				comment[COMMENT_LEN + 1];
}						t_champHeader;

typedef	struct			s_champ
{
	t_champHeader		header;
	t_byte				*body;
	t_process			*process;
	t_int32				nbr_process;
	t_byte				number;
	t_flags				flags;
}						t_champ;

typedef	struct			s_memory
{
	t_byte				mem[MEM_SIZE];
	t_byte				trace[MEM_SIZE];
}						t_memory;

typedef struct			s_vm
{
	void				(*cycleUpdated)(void);
	void				(*memUpdated)(t_memory *, int , int);
	void				(*processLoaded)(t_champ *c);
	void				(*playerLive)(t_champ *c, int);
	t_memory			memory;
	t_champ				champs[MAX_PLAYERS];
	t_byte				champ_count;
	t_int32				cycles_to_die;
	t_int32				cycles;
	t_int32				lives;
}						t_vm;

/*
** Callback
*/

/*
** int	current lives
*/

typedef void			(*t_livesDelta)(int);
typedef void			(*t_processDie)(t_champ *);
typedef void			(*t_playerDie)(t_champ *);
typedef void			(*t_playerWin)(t_champ *);

/*
** t_champ		sender
** int			live parametter
*/

typedef void			(*t_playerLive)(t_champ *, int);
typedef void			(*t_processLoaded)(t_champ *);

/*
**	t_memory * 	memory
**	int			offset
**	int			size (octe)
*/

typedef void			(*t_memUpdated)(t_memory *, int , int);
typedef int				(*t_loadChamps)(void);
typedef	void			(*t_cycleUpdated)(void);

/*
** Public
*/

typedef struct			s_render
{
	t_cycleUpdated		cycleUpdated;
	t_livesDelta		livesDelta;
	t_processDie		processDie;
	t_playerWin			playerWin;
	t_playerDie			playerDie;
	t_playerLive		playerLive;
	t_processLoaded		processLoaded;
	t_memUpdated		memUpdated;
}						t_render;

typedef struct			s_core
{
	t_loadChamps		loadChamps;
	t_render			render;
	t_vm				vm;
}						t_core;

#endif
