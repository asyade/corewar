/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:44:33 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/20 16:04:33 by acorbeau         ###   ########.fr       */
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

typedef struct			s_champDescrib
{
	char				*path;
	int					number;
}						t_champDescrib;

# define	P_VERBOSE	(1 << 1)
# define	P_NCURSE	(1 << 2)
# define	P_SH		(1 << 3)
# define	P_DUMP		(1 << 4)
# define	P_DUMPREP	(1 << 5)
# define	P_SOUND		(1 << 6)
# define	P_SHOWAFF	(1 << 7)

# define	PV_ESSENTAL	(0)
# define	PV_LIVES	(1 << 0)
# define	PV_CYCLES	(1 << 1)
# define	PV_OPS		(1 << 2)
# define	PV_DEATH	(1 << 3)
# define	PV_MOVES	(1 << 4)
# define	PV_DMPINST	(1 << 5)

typedef struct			s_param
{
	t_int32				flag;
	t_int32				verbose;
	t_int32				dump;
	t_int32				basedump;
	t_int32				count;
	t_int32				verbdellay;
	t_champDescrib		champs[4];
}						t_param;

typedef	struct			s_process
{
	int					id;
	t_reg				reg[REG_NUMBER];
	t_vptr				pc;
	t_vptr				cc;
	t_vptr				zc;
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
	t_param				*params;
	void		 		(*cycleUpdated)(void);
	void				(*memUpdated)(t_memory *, int , int);
	void				(*processLoaded)(t_champ *c);
	void				(*playerLive)(t_champ *c, int);
	void				(*playerDie)(t_champ *c);
	void				(*liveDelta)(int);
	void				(*instLoaded)(t_champ *, t_process *);
	void				(*pcUpdated)(t_process *pc);
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
typedef void			(*t_instLoaded)(t_champ *c, t_process *pc);
typedef void			(*t_pcUpdated)(t_process *pc);

/*
**	t_memory * 	memory
**	int			offset
**	int			size (octe)
*/

typedef void			(*t_memUpdated)(t_memory *, int , int);
typedef int				(*t_loadChamps)(void);
typedef	void			(*t_cycleUpdated)(void);
typedef void			(*t_envDone)(t_vm *vm);
typedef void			(*t_cycleToDieDelta)(int ctd);

/*
** Public
*/

typedef struct			s_render
{
	t_cycleUpdated		cycleUpdated;
	t_cycleToDieDelta	cycleToDieDelta;
	t_livesDelta		livesDelta;
	t_processDie		processDie;
	t_playerWin			playerWin;
	t_playerDie			playerDie;
	t_playerLive		playerLive;
	t_processLoaded		processLoaded;
	t_memUpdated		memUpdated;
	t_envDone			envDone;
	t_instLoaded		instLoaded;
	t_pcUpdated			pcUpdated;
}						t_render;

typedef struct			s_core
{
	t_loadChamps		loadChamps;
	t_render			render;
	t_vm				vm;
}						t_core;

#endif
