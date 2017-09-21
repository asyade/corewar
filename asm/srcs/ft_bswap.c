/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 07:14:49 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:38:19 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Endianness swap
*/

inline uint16_t	ft_bswap_u16(uint16_t to_swap)
{
	uint16_t	tmp;

	tmp = 0 | (to_swap >> 8);
	tmp |= to_swap << 8;
	return (tmp);
}

inline uint32_t	ft_bswap_u32(uint32_t to_swap)
{
	uint32_t	tmp;

	tmp = 0 | ((to_swap >> 24) & 0xFF);
	tmp |= (to_swap >> 8) & 0xFF00;
	tmp |= (to_swap << 8) & 0xFF0000;
	tmp |= (to_swap << 24) & 0xFF000000;
	return (tmp);
}
