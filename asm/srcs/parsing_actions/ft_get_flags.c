/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 03:15:02 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/29 04:07:13 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static NORETURN	ft_param_error(char *param)
{
	g_dk_info.content = param;
	ft_diagnostic(&g_dk_info, ASM_PARAM_ERROR, EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

t_info			ft_get_flags(int argc, char **argv)
{
	t_info	flags;

	ft_bzero(&flags, sizeof(flags));
	if (argc == 1)
		ft_put_asm_usage(NULL);
	if (argc > 2)
	{
		flags.flags = ft_parse_flags(argv[1]);
		if (flags.flags.bits.output && argc < 4)
		{
			g_dk_info.content = NULL;
			ft_diagnostic(&g_dk_info, NO_FILE_PROVIDED, EXIT_FAILURE);
		}
		else if (argc > 4)
			ft_param_error(argv[4]);
		else
			flags.output = argv[2];
	}
	return (flags);
}
