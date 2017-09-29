/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sconvertor_decimal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:43:43 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:46:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_sconvertor_decimal(void *nbr, t_arg *arg, char *buf)
{
	char		*str;
	uint32_t	len;

	(void)arg;
	str = ft_static_lltoa(*(int64_t*)nbr);
	len = (uint32_t)ft_strlen((const char*)str);
	ft_memcpy(buf, str, len);
	return ((int32_t)len);
}
