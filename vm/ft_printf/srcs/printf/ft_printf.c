/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:15:35 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 22:01:37 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void		ft_jump_arg(const char *format, uint32_t *i)
{
	while (format[*i] && ft_strchr(VALID_CHARS, format[*i]))
		(*i)++;
}

static inline int32_t	ft_print_arg(const char *format
									, va_list *v_arg, uint32_t *i)
{
	t_arg			arg;
	int64_t			nbr;
	int32_t			printed_chars;

	ft_get_arg(format + (*i), v_arg, &arg);
	if (arg.conversion == 0)
		return (0);
	nbr = ft_cast(va_arg(*v_arg, void*), &arg);
	printed_chars = ft_convertor(&nbr, &arg);
	ft_jump_arg(format, i);
	return (printed_chars);
}

int						ft_printf(const char *format, ...)
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
		ft_static_put((format + i), (len = ft_strchr_index(format + i
													, '%')), 0);
		i += len;
		printed_chars += ft_print_arg(format, &v_arg, &i) + (int32_t)len;
	}
	va_end(v_arg);
	return (printed_chars);
}
