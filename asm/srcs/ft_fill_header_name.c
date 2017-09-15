/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_header_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:37:07 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/15 12:45:23 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_fill_header_name(t_semantic_unit *unit, t_bin_buffer *bin)
{
	uint64_t	len;

	len = ft_strlen(unit->tokens[1].token);
	if (bin->name_flag)
		return (ft_error(4, (char*[]){NAME_COMMENT_REDEFINITION, unit->tokens[0].token,
						AT_LINE, ft_static_ulltoa(unit->line_nbr)}, -1));
	if (len > PROG_NAME_LENGTH)
		return (ft_error(3, (char*[]){NAME_TOO_LONG, AT_LINE
						, ft_static_ulltoa(unit->line_nbr)}, -1));
	ft_memcpy(bin->header.prog_name, unit->tokens[1].token, len);
	bin->header.prog_name[len] = '\0';
	bin->name_flag = 1;
	return (0);
}
