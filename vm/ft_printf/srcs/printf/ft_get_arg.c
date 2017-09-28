/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 05:27:29 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 22:01:59 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void			ft_get_length_modifier(const char *str, t_arg *arg)
{
	unsigned int	i;

	i = 0;
	while (str[i] && !ft_strchr(CONVERSION_FLAGS, str[i]))
		i++;
	if (ft_strchr("lh", *(str + i - 1)))
	{
		if (*(str + i - 1) == 'l' && *(str + i - 2) == 'l')
			arg->len_mod = LL;
		else if (*(str + i - 1) == 'h' && *(str + i - 2) == 'h')
			arg->len_mod = HH;
		else if (*(str + i - 1) == 'l')
			arg->len_mod = L;
		else
			arg->len_mod = H;
	}
	else
		arg->len_mod = NORMAL;
}

t_arg						*ft_get_arg(const char *str, va_list *v_arg
										, t_arg *arg)
{
	(void)v_arg;
	arg->conversion = 0;
	ft_get_length_modifier(str, arg);
	ft_get_conversion(str, arg);
	return (arg);
}
