#ifndef COREWAR_H
# define COREWAR_H

# include <stdio.h>
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
char		*dump_parametters(t_int32 inst[6], int c);
void		pwarn(char *format, ...);
void		pcri(char *format, ...);
void		plog(char *format, ...);

/*
** Core.c
*/

void		core_load_callback(t_core *core);
t_core		*core_init();

/*
** Play.c
*/

t_byte		play(t_core *core);

t_param		*params(void);
t_param		*read_params(int ac, char **av);

#endif
