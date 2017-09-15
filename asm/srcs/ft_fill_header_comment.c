/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_header_comment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:42:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/15 12:44:04 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_fill_header_comment(t_semantic_unit *unit, t_bin_buffer *bin)
{
	uint64_t	len;

	if (bin->comment_flag)
		return (ft_error(4, (char*[]){NAME_COMMENT_REDEFINITION, unit->tokens[0].token,
						AT_LINE, ft_static_ulltoa(unit->line_nbr)}, -1));
	len = ft_strlen(unit->tokens[1].token);
	if (len > COMMENT_LENGTH)
		return (ft_error(3, (char*[]){COMMENT_TOO_LONG, AT_LINE
						, ft_static_ulltoa(unit->line_nbr)}, -1));
	ft_memcpy(bin->header.comment, unit->tokens[1].token, len);
	bin->header.comment[len] = '\0';
	bin->comment_flag = 1;
	return (0);
}

