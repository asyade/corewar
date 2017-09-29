/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bin_integrity.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 21:20:54 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/19 03:17:58 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline void	ft_check_bin_integrity(t_bin_buffer *bin)
{
	g_dk_info.content = NULL;
	if (!bin->name_flag)
		ft_diagnostic(&g_dk_info, UNAMED_BIN_FILE, 0);
	if (!bin->comment_flag)
		ft_diagnostic(&g_dk_info, NO_COMMENT_DEFINED, 0);
	if (!bin->offset)
		ft_diagnostic(&g_dk_info, EMPTY_TEXT, 0);
}
