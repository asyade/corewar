/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:51:09 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:52:29 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	int64_t		i;
	char		*printf_str;
	char		mine[4096];

	i = -1100000;
	while (i < 288888888)
	{
		asprintf(&printf_str, "%lld", i);
		mine = ft_static_lltoa(i);
			printf("real: %s == mine: %s\n", printf_str, mine);
		if (strcmp(printf_str, mine))
		{

			ft_error_exit(1, (char*[]){"FAILURE"}, EXIT_FAILURE);
		}
		free(printf_str);
		i++;
	}
	return (0);
}
