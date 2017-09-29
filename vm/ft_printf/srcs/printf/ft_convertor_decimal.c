/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertor_decimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:43:29 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 20:38:37 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_convertor_decimal(void *nbr, t_arg *arg)
{
	char		*str;
	uint32_t	len;

	(void)arg;
	str = ft_static_lltoa(*(int64_t*)nbr);
	len = (uint32_t)ft_strlen((const char*)str);
	ft_static_put(str, len, 0);
	return ((int32_t)len);
}
