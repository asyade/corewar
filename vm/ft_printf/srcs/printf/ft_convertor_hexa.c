/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertor_hexa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:41:01 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:32:31 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_convertor_hexa(void *nbr, t_arg *arg)
{
	char		*str;
	uint32_t	len;

	(void)arg;
	str = ft_static_ulltoa_base(*(uint64_t*)nbr, HEXA_MIN_CHARSET);
	len = (uint32_t)ft_strlen(str);
	ft_static_put("0000", 4 - len, 0);
	ft_static_put(str, len, 0);
	return (4);
}
