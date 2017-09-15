/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bin_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:21:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/15 12:47:47 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bin_buffer	*ft_create_bin_buffer(uint64_t capacity)
{
	t_bin_buffer	*bin;

	if (!(bin = (t_bin_buffer*)ft_memalloc(sizeof(t_bin_buffer) + sizeof(char) * capacity)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	bin->capacity = capacity;
	bin->offset = 0;
	bin->buffer = (char*)bin + sizeof(t_bin_buffer);
	bin->header.magic = COREWAR_EXEC_MAGIC;
	return (bin);
}
