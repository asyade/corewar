/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:50:59 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdio.h>
# include <stdint.h>
# include "libft.h"
# include "def.h"
# include "structs.h"
# include "memory.h"
# include "inst.h"
# include "cpu.h"
# include "vm.h"

/*
** Settings
*/

# define LOGGER_FD  ((getenv("silent") ? -1 : 1))
# define LOGGER_FILE "cw.trace"
# define DELLAY ((getenv("dellay")) ? atoi(getenv("dellay")) : 5000)

void		usage(void);

/*
** logger.c
*/

char		*ptstr(t_byte type);
char		*dump_parametters(t_vm *vm, t_process *pc, uint32_t nbr_param);
void		pwarn(char *format, ...);
void		pcri(char *format, ...);
void		plog(char *format, ...);

/*
** Dump.c
*/

# define DUMP_OPL	64
# define DUMP_LSIZE	(DUMP_OPL + (DUMP_OPL * 2) + (11 * DUMP_OPL))
# define DUMP_BASE	"0123456789abcdef"

/*
** Core.c
*/

# define MACRO_DUTURUF {{0, 0}, {0, 0}, {0, 0}, {0, 0}}

int			load_champs_default(t_param *p, t_core *core);
void		core_load_callback(t_core *core);
t_core		*core_init();

/*
** Play.c
*/

t_byte		play(t_core *core);

t_param		*params(void);
t_param		*read_params(int ac, char **av);

#endif
