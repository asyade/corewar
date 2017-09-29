/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sconvertor_hexa.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:45:31 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:47:51 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_sconvertor_hexa(void *nbr, t_arg *arg, char *buf)
{
	char		*str;
	uint32_t	len;

	(void)arg;
	str = ft_static_ulltoa_base(*(uint64_t*)nbr, HEXA_MIN_CHARSET);
	len = (uint32_t)ft_strlen(str);
	ft_memcpy(buf, "0000", 4 - len);
	ft_memcpy(buf + (4 - len), str, len);
	return (4);
}
