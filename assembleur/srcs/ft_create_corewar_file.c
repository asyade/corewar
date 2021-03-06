/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_corewar_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 06:39:51 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/29 03:31:44 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline void	ft_create_corewar_file(char *filename, t_bin_buffer *bin
								, t_asm_flags flags)
{
	int	fd;

	g_dk_info.content = NULL;
	if (-1 == (fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU
						| S_IRWXO | S_IRWXG)))
		ft_diagnostic(&g_dk_info, CREATE_FILE_ERROR, EXIT_FAILURE);
	write(fd, &bin->header, sizeof(t_header));
	write(fd, bin->buffer, bin->offset);
	if (-1 == (close(fd)))
		perror(BIN_NAME);
	if (!flags.bits.output)
		free(filename);
	free(bin->buffer);
	free(bin);
}
