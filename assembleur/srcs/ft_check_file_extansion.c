/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_extansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 01:17:28 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:25:33 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_check_file_extansion(char *filename)
{
	size_t	len;

	ft_init_dk_info(&g_dk_info);
	len = ft_strlen(filename);
	if (len <= 2)
		ft_put_asm_usage(filename);
	len -= 2;
	if (!ft_strequ(filename + len, ASM_FILE_EXTENSION))
	{
		g_dk_info.content = filename;
		g_dk_info.force_no_abort = 1;
		ft_diagnostic(&g_dk_info, INVALID_FILE_EXTENSION, 0);
		ft_put_asm_usage(NULL);
	}
}
