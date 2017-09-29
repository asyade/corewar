/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 03:06:53 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/29 04:09:31 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

NORETURN			ft_flags_usage(char invalid_flag)
{
	static char	buf[2];

	buf[0] = invalid_flag;
	g_dk_info.content = buf;
	g_dk_info.force_no_abort = 1;
	ft_diagnostic(&g_dk_info, ERR_INVALID_FLAG, 0);
	ft_error_exit(1, (char*[]){ASM_USAGE}, EXIT_FAILURE);
}

static NORETURN		ft_flag_format(char *str)
{
	g_dk_info.content = str;
	g_dk_info.force_no_abort = 1;
	ft_diagnostic(&g_dk_info, INVALID_FLAGS_FORMAT, 0);
	ft_error_exit(1, (char*[]){ASM_USAGE}, EXIT_FAILURE);
}

t_asm_flags			ft_parse_flags(char *argv)
{
	static char	flags_char[] = {'o'};
	t_asm_flags	flags;
	uint32_t	i;
	uint32_t	u;

	flags.flags = 0;
	if (*argv != '-' || (argv[0] && !argv[1]))
		ft_flag_format(argv);
	u = 1;
	while (argv[u])
	{
		i = 0;
		while (i < sizeof(flags_char) / sizeof(char))
		{
			if (flags_char[i] == argv[u])
			{
				flags.flags |= 1 << i;
				break ;
			}
			if (++i >= sizeof(flags_char) / sizeof(char))
				ft_flags_usage(argv[u]);
		}
		u++;
	}
	return (flags);
}
