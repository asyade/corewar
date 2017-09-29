/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 06:23:54 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 22:02:08 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long			ft_signed_cast(void *ptr, t_arg *arg)
{
	if (arg->len_mod == L)
		return ((long)ptr);
	else if (arg->len_mod == LL)
		return ((long long)ptr);
	else if (arg->len_mod == H)
		return ((short)((long long)ptr));
	else if (arg->len_mod == HH)
		return ((char)(long long)ptr);
	else
		return ((int)(long long)ptr);
}

static unsigned long long	ft_unsigned_cast(void *ptr
											, t_arg *arg)
{
	if (arg->len_mod == L)
		return ((unsigned long)ptr);
	else if (arg->len_mod == LL)
		return ((unsigned long long)ptr);
	else if (arg->len_mod == H)
		return ((unsigned short)(long long)ptr);
	else if (arg->len_mod == HH)
		return ((unsigned char)(long long)ptr);
	else
		return ((unsigned int)(long long)ptr);
}

int64_t						ft_cast(void *ptr, t_arg *arg)
{
	if (ft_strchr("Dd", arg->conversion))
		return ((int64_t)ft_signed_cast(ptr, arg));
	else if (ft_strchr("xX", arg->conversion))
		return ((int64_t)ft_unsigned_cast(ptr, arg));
	return ((int64_t)ptr);
}
