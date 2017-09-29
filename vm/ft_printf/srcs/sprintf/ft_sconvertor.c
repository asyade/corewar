/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sconvertor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:42:24 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:51:36 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_sconvertor(void *nbr, t_arg *arg, char *buf)
{
	static const t_sprintf_conv conv[] = {
	{ 'x', &ft_sconvertor_hexa },
	{ 'd', &ft_sconvertor_decimal },
	{ 's', &ft_sconvertor_str }};
	uint32_t					i;

	i = 0;
	if (!arg->conversion)
		return (-1);
	while (i < sizeof(conv) / sizeof(t_conv))
	{
		if (conv[i].conversion == arg->conversion)
			return (conv[i].f(nbr, arg, buf));
		i++;
	}
	return (0);
}
