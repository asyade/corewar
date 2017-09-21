/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_header_comment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:42:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:39:36 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_fill_header_comment(t_semantic_unit *unit, t_bin_buffer *bin)
{
	uint64_t	len;

	g_dk_info.content = unit->tokens[0].token;
	g_dk_info.location.column = unit->tokens[0].column;
	g_dk_info.location.len = unit->tokens[0].len;
	if (bin->comment_flag)
		return (ft_diagnostic(&g_dk_info, NAME_COMMENT_REDEFINITION, -1));
	len = ft_strlen(unit->tokens[1].token);
	g_dk_info.content = unit->tokens[1].token;
	g_dk_info.location.column = unit->tokens[1].column;
	g_dk_info.location.len = unit->tokens[1].len;
	if (!len)
		return (-1);
	unit->tokens[1].token[len - 1] = '\0';
	if (len > COMMENT_LENGTH)
		return (ft_diagnostic(&g_dk_info, COMMENT_TOO_LONG, -1));
	ft_memcpy(bin->header.comment, unit->tokens[1].token + 1, len - 1);
	bin->header.comment[len] = '\0';
	bin->comment_flag = 1;
	return (0);
}
