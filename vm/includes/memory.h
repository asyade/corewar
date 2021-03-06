/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:56:06 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# define BSWAP16 __builtin_bswap16
# define BSWAP32 __builtin_bswap32

# define MEMPTR(ptr) (((ptr) % MEM_SIZE))
# define ABSPTR(ptr) ((ptr < 0) ? (MEM_SIZE - (-(MEMPTR(ptr)))) : (MEMPTR(ptr)))

void		mem_write(t_vm *vm, t_byte *buff, t_memzone zone, t_byte trace);
void		mem_writeint(t_vm *vm, t_int32 val, t_vptr offset, t_byte trace);

t_int32		mem_readn(t_memory *mem, t_vptr ptr, t_byte n);
t_int32		mem_readint(t_memory *mem, int offset);
t_int32		mem_readshort(t_memory *mem, int offset);
t_byte		mem_readbyte(t_memory *mem, int offset);

#endif
