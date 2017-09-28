/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertor_address.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:40:24 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 20:41:23 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_convertor_address(void *nbr, t_arg *arg)
{
	char		*str;
	uint32_t	len;

	(void)arg;
	str = ft_static_ulltoa_base(*(uintptr_t*)nbr, HEXA_MIN_CHARSET);
	len = (uint32_t)ft_strlen(str);
	ft_static_put("0x", 2, 0);
	ft_static_put(str, len, 0);
	return ((int32_t)len + 2);
}
