/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:45 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 10:07:13 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Attention toutes les fonctions switch bigEdianes<->littelEndiannes
** sauf mem_write
**
** Pareille que plus bas
*/

void		mem_write(t_vm *vm, t_byte *buff, t_memzone zone, t_byte trace)
{
	zone.offset = ABSPTR(zone.offset);
	while (zone.size--)
	{
		vm->memory.trace[zone.offset] = trace;
		vm->memory.mem[zone.offset++] = *buff++;
		zone.offset = MEMPTR(zone.offset);
	}
	if (vm->mem_updated)
		vm->mem_updated(&vm->memory, zone.offset, zone.size);
}

/*
** On utilise pas de memset pour ne pas avoire d'overflow
** ex write 4 -> 4093 = segfault si pas de % MEM_SIZE
*/

void		mem_writeint(t_vm *vm, t_int32 val, t_vptr offset, t_byte trace)
{
	offset = ABSPTR(offset);
	vm->memory.mem[MEMPTR(offset + 0)] = (val & 0xFF000000) >> 24;
	vm->memory.mem[MEMPTR(offset + 1)] = (val & 0x00FF0000) >> 16;
	vm->memory.mem[MEMPTR(offset + 2)] = (val & 0x0000FF00) >> 8;
	vm->memory.mem[MEMPTR(offset + 3)] = val & 0x000000FF;
	vm->memory.trace[MEMPTR(offset + 3)] = trace;
	vm->memory.trace[MEMPTR(offset + 2)] = trace;
	vm->memory.trace[MEMPTR(offset + 1)] = trace;
	vm->memory.trace[MEMPTR(offset + 0)] = trace;
	if (vm->mem_updated)
		vm->mem_updated(&vm->memory, offset, 4);
}

t_int32		mem_readint(t_memory *mem, int offset)
{
	return ((int32_t)BSWAP32(mem_readn(mem, offset, 4)));
}

t_int32		mem_readshort(t_memory *mem, int offset)
{
	return ((int16_t)BSWAP16((mem_readn(mem, offset, 2))));
}

t_byte		mem_readbyte(t_memory *mem, int offset)
{
	return (mem->mem[ABSPTR(offset)]);
}
