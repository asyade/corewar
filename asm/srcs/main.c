/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:07:25 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/13 10:05:40 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*buffer;

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
		buffer = ft_parse(fd);
		if (-1 == (close(fd)))
		{
			perror(BIN_NAME);
			exit(EXIT_FAILURE);
		}
//ft_create_corewar_file(argv[1], buffer);
	}
	return (0);
}
