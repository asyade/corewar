/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/28 23:24:53 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdarg.h>
#include <fcntl.h>

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
	va_list	args;

	if (LOGGER_FD < 0)
		return ;
	ft_sprintf(buffer, "\e[31mwarning\e[0m: ");
	va_start(args, format);
	vsprintf(buffer + 18, format, args);
	va_end(args);
	pflush(buffer);
}

void		pcri(char *format, ...)
{
	char	buffer[4096];
	va_list	args;

	if (LOGGER_FD < 0)
		return ;
	ft_sprintf(buffer, "\e[31;1;4;5;7mcritical\e[0m : ");
	va_start(args, format);
	vsprintf(buffer + 26, format, args);
	va_end(args);
	pflush(buffer);
	exit(1);
}

void		plog(char *format, ...)
{
	char	buffer[4096];
	va_list	args;

	if (LOGGER_FD < 0)
		return ;
	ft_sprintf(buffer, "\e[32minfo\e[0m: ");
	va_start(args, format);
	vsprintf(buffer + 15, format, args);
	va_end(args);
	pflush(buffer);
}
