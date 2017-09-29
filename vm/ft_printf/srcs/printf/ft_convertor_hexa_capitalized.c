/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertor_hexa_capitalized.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:39:45 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 20:37:57 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_convertor_hexa_capitalized(void *nbr, t_arg *arg)
{
	char		*str;
	uint32_t	len;

	(void)arg;
	str = ft_static_ulltoa_base(*(uint64_t*)nbr, HEXA_MAX_CHARSET);
	len = (uint32_t)ft_strlen(str);
	ft_static_put(str, len, 0);
	return ((int32_t)len);
}
