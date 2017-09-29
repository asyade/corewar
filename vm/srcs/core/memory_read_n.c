/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_read_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:45 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:02:09 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_int32		mem_readn(t_memory *mem, t_vptr ptr, t_byte n)
{
	t_int32		ret;

	ret = 0;
	ptr = ABSPTR(ptr);
	while (n--)
	{
		ret = ret << 8;
		ret |= mem->mem[MEMPTR(ptr + n)];
	}
	return (ret);
}
