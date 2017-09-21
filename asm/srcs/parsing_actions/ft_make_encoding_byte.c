/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_encoding_byte.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 03:11:48 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:49:19 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline uint8_t	ft_make_encoding_byte(t_arg_type *args, uint64_t nbr_args)
{
	static const	t_encoding_byte encoding_bytes[] = {
		{T_REG, REG_CODE},
		{T_DIR, DIR_CODE},
		{T_IND, IND_CODE}};
	uint32_t						i;
	uint32_t						u;
	uint8_t							encoding_byte;

	i = 0;
	encoding_byte = 0;
	while (i < nbr_args)
	{
		u = 0;
		while (u < sizeof(encoding_bytes) / sizeof(t_encoding_byte))
		{
			if ((args[i] & encoding_bytes[u].arg_type))
				encoding_byte |= encoding_bytes[u].code << (6 - (i * 2));
			u++;
		}
		i++;
	}
	return (encoding_byte);
}
