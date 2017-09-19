/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_header_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:37:07 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/19 03:35:04 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_fill_header_name(t_semantic_unit *unit, t_bin_buffer *bin)
{
	uint64_t	len;

	g_dk_info.content = unit->tokens[0].token;
	g_dk_info.location.column = unit->tokens[0].column;
	g_dk_info.location.len = unit->tokens[0].len;
	if (bin->name_flag)
		return (ft_diagnostic(&g_dk_info, NAME_COMMENT_REDEFINITION, -1));
	len = ft_strlen(unit->tokens[1].token);
	g_dk_info.content = unit->tokens[1].token;
	g_dk_info.location.column = unit->tokens[1].column;
	g_dk_info.location.len = unit->tokens[1].len;
	if (!len)
		return (ft_diagnostic(&g_dk_info, NAME_TOO_SHORT, -1));
	unit->tokens[1].token[len - 1] = '\0';
	if (len - 1 > PROG_NAME_LENGTH)
		return (ft_diagnostic(&g_dk_info, NAME_TOO_LONG, -1));
	ft_memcpy(bin->header.prog_name, unit->tokens[1].token + 1, len - 1);
	bin->header.prog_name[len] = '\0';
	bin->name_flag = 1;
	return (0);
}
