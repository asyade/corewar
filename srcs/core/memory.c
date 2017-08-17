/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 21:20:45 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/17 17:48:41 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Attention toutes les fonctions switch bigEdianes<->littelEndiannes
** sauf mem_write
**
** Pareille que plus bas
*/

void        mem_write(t_vm *vm, t_byte *buff, t_vsize size, t_vptr offset, t_byte trace)
{
    offset = ABSPTR(offset);
    while (size--)
    {
        vm->memory.trace[offset] = trace;        
        vm->memory.mem[offset++] = *buff++;
        offset = MEMPTR(offset);
    }
    if (vm->memUpdated)
        vm->memUpdated(&vm->memory, offset, size);
}

/*
** On utilise pas de memset pour ne pas avoire d'overflow
** ex write 4 -> 4093 = segfault si pas de % MEM_SIZE
*/

void        mem_writeint(t_vm *vm, t_int32 val, t_vptr offset, t_byte trace)
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
    if (vm->memUpdated)
        vm->memUpdated(&vm->memory, offset, 4);
}

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

t_int32        mem_readint(t_memory *mem, int offset)
{
    return ((int32_t)BSWAP32(mem_readn(mem, offset, 4)));
}

t_int32        mem_readshort(t_memory *mem, int offset)
{
    return ((int16_t)BSWAP16((mem_readn(mem, offset, 2))));
}

t_byte        mem_readbyte(t_memory *mem, int offset)
{
    return (mem->mem[ABSPTR(offset)]);
}