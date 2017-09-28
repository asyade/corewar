/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertor_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:40:50 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:51:53 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_sconvertor_str(void *str, t_arg *arg, char *buf)
{
	uint32_t	len;

	(void)arg;
	if (!str)
	{
		ft_static_put(str, 0, 0);
		return ((int32_t)sizeof("(null)"));
	}
	len = (uint32_t)ft_strlen(*(char**)str);
	ft_memcpy(buf, *(char**)str, len);
	return ((int32_t)len);
}
