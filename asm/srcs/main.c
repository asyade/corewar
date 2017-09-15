/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:07:25 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/15 23:24:56 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_bin_buffer_hex_dump(t_bin_buffer *buffer)
{
	ft_putstr(buffer->buffer);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_bin_buffer	*bin;

	if (argc > 2)
		ft_put_asm_usage(argv[2]);
	else if (argc == 1)
		ft_put_asm_usage(NULL);
	else
	{
		ft_check_file_extansion(argv[1]);
		if (-1 == (fd = open(argv[1], O_RDONLY)))
		{
			perror(BIN_NAME);
			exit(EXIT_FAILURE);
		}
		bin = ft_parse(fd);
		ft_bin_buffer_hex_dump(bin);
		if (-1 == (close(fd)))
		{
			perror(BIN_NAME);
			exit(EXIT_FAILURE);
		}
//ft_create_corewar_file(argv[1], buffer);
	}
	return (0);
}
