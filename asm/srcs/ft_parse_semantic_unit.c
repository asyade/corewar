/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_semantic_unit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:51:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/17 08:56:08 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline int32_t	ft_handler_verbose_structure(t_semantic_unit *unit
													, t_bin_buffer *bin)
{
	if (unit->tokens_nbr > 1 && unit->tokens[1].token_type == CONTENT)
	{
		if (unit->tokens[0].token_type == NAME)
			return (ft_fill_header_name(unit, bin));
		else
			return (ft_fill_header_comment(unit, bin));
	}
	else if (unit->tokens_nbr == 1)
		return (ft_error(4, (char*[]){EXPECTED_EXPRESSION, unit->tokens[0].token,
						AT_LINE, ft_static_ulltoa(unit->line_nbr)}, -1));
	else
		return (ft_error(4, (char*[]){INVALID_EXPRESSION, unit->tokens[1].token
				, AT_LINE, ft_static_ulltoa(unit->line_nbr)}, -1));
}

static inline int32_t	ft_handler_instruction_structure(t_semantic_unit *unit
														 , uint64_t index, t_bin_buffer *bin)
{
	if (!ft_check_params_integrity(unit, index))
		return (-1);
	if (!ft_get_params_value(unit, index))
		return (-1);
	ft_fill_bin_with_instruction(unit, index, bin);
	return (0);
}

int32_t			ft_parse_semantic_unit(t_semantic_unit *unit, t_bin_buffer *bin)
{
	uint64_t	i;

	i = 0;
	if (unit->tokens_nbr == 0)
		return (0);
	if (unit->tokens[i].token_type == NAME
		|| unit->tokens[i].token_type == COMMENT)
		return (ft_handler_verbose_structure(unit, bin));
	if (unit->tokens[i].token_type == LABEL)
	{
		if (unit->tokens_nbr > 1)
			i++;
		else
			return (0);
	}
	if (unit->tokens[i].token_type == INSTRUCTION)
		return (ft_handler_instruction_structure(unit, i, bin));
	else
		return (-1); //
}
