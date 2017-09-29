/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 03:06:02 by acorbeau         ###   ########.fr       */
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
# include "ft_printf.h"

# define PF1 (uint8_t[]){0, 0, 0}
# define PF2 (uint8_t[]){2, 0}
# define PF3 (uint8_t[]){0, 0}
# define PF4 (uint8_t[]){0, 0, 0}
# define PF5 (uint8_t[]){0, 0, 0}
# define PF6 (uint8_t[]){1, 1, 0}
# define PF7 (uint8_t[]){1, 1, 0}
# define PF8 (uint8_t[]){1, 1, 0}
# define PF9 (uint8_t[]){0, 0, 0}
# define PF10 (uint8_t[]){1, 1, 0}
# define PF11 (uint8_t[]){0, 1, 1}
# define PF12 (uint8_t[]){0, 0, 0}
# define PF13 (uint8_t[]){1, 0}
# define PF14 (uint8_t[]){1, 1, 0}
# define PF15 (uint8_t[]){0, 0, 0}
# define PF16 (uint8_t[]){0, 0, 0}

/*
** Settings
*/

void		usage(void);

/*
** logger.c
*/

char		*ptstr(t_byte type);
char		*dump_parametters(t_vm *vm, t_process *pc, uint32_t nbr_param);

/*
** Dump.c
*/

# define DUMP_OPL	64
# define DUMP_LSIZE	(DUMP_OPL + (DUMP_OPL * 2) + (11 * DUMP_OPL))
# define DUMP_BASE	"0123456789abcdef"

/*
** Core.c
*/

# define MACRO_DUTURUF {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}

void		champs_sort(t_vm *vm);
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
