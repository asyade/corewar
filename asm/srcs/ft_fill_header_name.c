/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_header_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:37:07 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/17 11:46:28 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_fill_header_name(t_semantic_unit *unit, t_bin_buffer *bin)
{
	uint64_t	len;

	if (bin->name_flag)
		return (ft_error(4, (char*[]){NAME_COMMENT_REDEFINITION, unit->tokens[0].token,
						AT_LINE, ft_static_ulltoa(unit->line_nbr)}, -1));
	len = ft_strlen(unit->tokens[1].token);
	if (!len)
		return (-1);
	unit->tokens[1].token[len - 1] = '\0';
	if (len - 1 > PROG_NAME_LENGTH)
		return (ft_error(3, (char*[]){NAME_TOO_LONG, AT_LINE
						, ft_static_ulltoa(unit->line_nbr)}, -1));
	ft_memcpy(bin->header.prog_name, unit->tokens[1].token + 1, len - 1);
	bin->header.prog_name[len] = '\0';
	bin->name_flag = 1;
	return (0);
}
