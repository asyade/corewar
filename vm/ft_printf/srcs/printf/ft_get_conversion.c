/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:27:59 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 20:11:16 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline void			ft_get_conversion(const char *str, t_arg *arg)
{
	int		i;

	i = 0;
	while (str[i] && (ft_strchr(VALID_CHARS, str[i])))
	{
		if (ft_strchr(CONVERSION_FLAGS, str[i]))
		{
			arg->conversion = str[i];
			break ;
		}
		else
			i++;
	}
	arg->conversion = str[i];
}
