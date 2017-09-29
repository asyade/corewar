/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bin_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:21:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/18 15:44:49 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline t_bin_buffer	*ft_create_bin_buffer(uint64_t capacity)
{
	t_bin_buffer	*bin;

	if (!(bin = (t_bin_buffer*)ft_memalloc(sizeof(t_bin_buffer))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	bin->capacity = capacity;
	bin->offset = 0;
	if (!(bin->buffer = (char*)ft_memalloc(sizeof(char) * capacity)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	bin->header.magic = ft_bswap_u32(COREWAR_EXEC_MAGIC);
	return (bin);
}

inline t_bin_buffer	*ft_realloc_bin_buffer(t_bin_buffer *bin)
{
	char	*tmp;

	if (!(tmp = (char*)ft_memalloc(bin->capacity * 2 * sizeof(char))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	ft_memcpy(tmp, bin->buffer, bin->offset);
	free(bin->buffer);
	bin->buffer = tmp;
	bin->capacity *= 2;
	return (bin);
}
