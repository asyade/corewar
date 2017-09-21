/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:07:25 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/20 14:03:23 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_bin_buffer_hex_dump(t_bin_buffer *buffer)
{
	uint64_t	i;

	i = 0;
	printf("bin buff_size: %lx\n", buffer->offset);
	while (i < buffer->offset)
	{
		if (i % 32 == 0)
			printf("\n%8p: ", (void*)(i));
		printf("%02hhx ", buffer->buffer[i]);
		i++;
	}
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
		ft_init_dk_info(&g_dk_info);
		if (-1 == (fd = open(argv[1], O_RDONLY)))
		{
			perror(BIN_NAME);
			exit(EXIT_FAILURE);
		}
		bin = ft_parse(fd);
		bin->header.prog_size = ft_bswap_u32((uint32_t)bin->offset);
//		printf("bin_size: %x\n", /* ft_bswap_u32((uint32_t)bin->offset) */bin->header.prog_size);
//		ft_bin_buffer_hex_dump(bin);
		(void)ft_bin_buffer_hex_dump;
		if (-1 == (close(fd)))
		{
			perror(BIN_NAME);
			exit(EXIT_FAILURE);
		}
		ft_create_corewar_file(ft_get_bin_filename(argv[1]), bin);
	}
	return (0);
}
