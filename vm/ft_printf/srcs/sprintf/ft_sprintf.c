/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:39:27 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 22:01:21 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void		ft_jump_arg(const char *format, uint32_t *i)
{
	while (format[*i] && ft_strchr(VALID_CHARS, format[*i]))
		(*i)++;
}

static inline int32_t	ft_print_arg(const char *format
								, va_list *v_arg, uint32_t *i, char *str)
{
	t_arg			arg;
	int64_t			nbr;
	int32_t			printed_chars;

	ft_get_arg(format + (*i), v_arg, &arg);
	if (arg.conversion == 0)
		return (0);
	nbr = ft_cast(va_arg(*v_arg, void*), &arg);
	printed_chars = ft_sconvertor(&nbr, &arg, str);
	ft_jump_arg(format, i);
	return (printed_chars);
}

int						ft_sprintf(char *str, const char *format, ...)
{
	uint32_t	i;
	uint32_t	len;
	int32_t		printed_chars;
	va_list		v_arg;

	i = 0;
	printed_chars = 0;
	va_start(v_arg, format);
	while (format[i])
	{
		ft_memcpy(str + printed_chars, (format + i)
				, (len = ft_strchr_index(format + i, '%')));
		i += len;
		printed_chars += ft_print_arg(format, &v_arg, &i, str
						+ printed_chars + len) + (int32_t)len;
	}
	va_end(v_arg);
	str[printed_chars] = '\0';
	return (printed_chars);
}
