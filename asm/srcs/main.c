/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:07:25 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/29 04:06:42 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	int				fd;
	t_bin_buffer	*bin;
	t_info			info;

	info = ft_get_flags(argc, argv);
	ft_check_file_extansion(argv[1 + info.flags.bits.output
								+ !!info.flags.flags]);
	if (-1 == (fd = open(argv[1 + info.flags.bits.output
							+ !!info.flags.flags], O_RDONLY)))
		ft_error_exit(1, (char*[]){strerror(errno)}, EXIT_FAILURE);
	bin = ft_parse(fd);
	bin->header.prog_size = ft_bswap_u32((uint32_t)bin->offset);
	if (-1 == (close(fd)))
		ft_error_exit(1, (char*[]){strerror(errno)}, EXIT_FAILURE);
	if (info.flags.bits.output)
		ft_create_corewar_file(info.output, bin, info.flags);
	else
		ft_create_corewar_file(ft_get_bin_filename(argv[1]), bin, info.flags);
	return (0);
}
