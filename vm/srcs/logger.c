#include "corewar.h"
#include <stdarg.h>
#include <fcntl.h>

//TODO : replace with my printf

static void	pflush(char *buff)
{
	int	fd;

	fd = LOGGER_FD;
	if (fd <= 0)
	{
		return ;
	}
	ft_putstr_fd(buff, fd);
}

char		*ptstr(t_byte type)
{
	if (type == T_REG)
		return ("T_REG");
	else if (type == T_DIR)
		return ("T_DIR");
	else if (type == T_IND)
		return ("T_IND");
	return ("T_UNDEF");
}

void		pwarn(char *format, ...)
{
	char	buffer[4096];

	if (LOGGER_FD < 0)
		return ;
	va_list	args;
	sprintf(buffer, "\e[31mwarning\e[0m: ");
	va_start (args, format);
	vsprintf (buffer + 18, format, args);
	va_end (args);
	pflush(buffer);
}

void		pcri(char *format, ...)
{
	char	buffer[4096];
	va_list	args;

	if (LOGGER_FD < 0)
		return ;
	sprintf(buffer, "\e[31;1;4;5;7mcritical\e[0m: ");
	va_start (args, format);
	vsprintf (buffer + 25, format, args);
	va_end (args);
	pflush(buffer);
	exit(1);
}

void		plog(char *format, ...)
{
	char	buffer[4096];
	va_list	args;

	if (LOGGER_FD < 0)
		return ;
	sprintf(buffer, "\e[32minfo\e[0m: ");
	va_start (args, format);
	vsprintf (buffer + 15, format, args);
	va_end (args);
	pflush(buffer);
}

char		*reg_str(t_int32 inst[6], int i)
{
	static char	st[2] = (char[2]) { '\0', '\0' };

	st[0] = '\0';
	st[1] = '\0';
	if (i == 1 && IP1(inst[1]) == T_REG)
		st[0] = 'r';
	if (i == 2 && IP2(inst[1]) == T_REG && inst[0] != 3)
		st[0] = 'r';
	if (i == 3 && IP3(inst[1]) == T_REG)
		st[0] = 'r';
	if (i == 4 && IP4(inst[1]) == T_REG)
		st[0] = 'r';
	return (st);
}

char		*dump_parametters(t_process *pc, uint32_t nbr_param)
{
	const uint8_t	*print_type[OP_NBR] = {(uint8_t[]){0, 0, 0},
	(uint8_t[]){1, 0},
	(uint8_t[]){0, 0},
	(uint8_t[]){0, 0, 0},
	(uint8_t[]){0, 0, 0},
	(uint8_t[]){1, 1, 0},
	(uint8_t[]){1, 1, 0},
	(uint8_t[]){0, 0, 0},
	(uint8_t[]){0, 0, 0},
	(uint8_t[]){1, 1, 0},
	(uint8_t[]){0, 1, 1},
	(uint8_t[]){0, 0, 0},
	(uint8_t[]){1, 0},
	(uint8_t[]){1, 1, 0},
	(uint8_t[]){0, 0, 0},
	(uint8_t[]){0, 0, 0}};
	static char		buff[1024];
	char			*bptr;
	uint32_t		i;

	bptr = buff;
	*bptr = '\0';
	if (LOGGER_FD < 0)
		return (buff);
	i = 0;
	if (nbr_param == 0)
		sprintf(buff, " %d", pc->inst[1]);
	while (i < nbr_param)
	{
		if (!print_type[pc->inst[0] - 1][i])
			bptr += sprintf(bptr," %s%d", reg_str(pc->inst, i + 1), pc->inst[i + 2]);//TODO: replace printf
		else
			bptr += sprintf(bptr," %d", param_dirval(pc, i + 1));//TODO: replace printf
		i++;
	}
	return (buff);
}

/*
** char     	*dump_parametters(t_int32 inst[6], int c)
** {
**     static char buff[1024];
**     char        *bptr;
**
**     bptr = buff;
**     *bptr = '\0';
** 	if (LOGGER_FD < 0)
** 		return (buff);
** 	if (c == 0)
** 		sprintf(buff, "%d", inst[1]);
**     if (c >= 1)
**         bptr += sprintf(buff,"%s:%d", ptstr(IP1(inst[1])), inst[2]);//TODO: replace printf
**     if (c >= 2)
**         bptr += sprintf(bptr,", %s:%d", ptstr(IP2(inst[1])), inst[3]);//TODO: replace printf
**     if (c >= 3)
**         bptr += sprintf(bptr,", %s:%d", ptstr(IP3(inst[1])), inst[4]);//TODO: replace printf
**     if (c >= 4)
** 		bptr += sprintf(bptr,", %s:%d", ptstr(IP4(inst[1])), inst[5]);//TODO: replace printf
** 	return (buff);
** }
*/
