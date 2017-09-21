/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:07:25 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:25:35 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
		bin->header.prog_size = ft_bswap_u32((uint32_t)bin->offset);
		if (-1 == (close(fd)))
		{
			perror(BIN_NAME);
			exit(EXIT_FAILURE);
		}
		ft_create_corewar_file(ft_get_bin_filename(argv[1]), bin);
	}
	return (0);
}
