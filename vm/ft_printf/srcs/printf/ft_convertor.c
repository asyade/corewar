/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:36:49 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:50:24 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	ft_convertor(void *nbr, t_arg *arg)
{
	static const t_conv conv[] = {
	{ 'x', &ft_convertor_hexa },
	{ 'd', &ft_convertor_decimal },
	{ 's', &ft_convertor_str }};
	uint32_t			i;

	i = 0;
	if (!arg->conversion)
		return (-1);
	while (i < sizeof(conv) / sizeof(t_conv))
	{
		if (conv[i].conversion == arg->conversion)
			return (conv[i].f(nbr, arg));
		i++;
	}
	return (0);
}
