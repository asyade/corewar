/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_token_decimal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 21:22:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/17 21:35:33 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_is_token_decimal(char *token)
{
	uint64_t	i;

	i = 0;
	while (token[i])
	{
		if (!ft_strchr(CHARSET_DECIMAL, token[i]))
			return (0);
		i++;
	}
	return (1);
}
