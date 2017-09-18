/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_params_integrity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 04:27:52 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/18 15:36:05 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_check_params_integrity(t_semantic_unit *unit, uint64_t index)
{
	uint64_t	i;

	if (unit->tokens_nbr - index - 1 > op_tab[unit->tokens[index].token_content.opcode - 1].nbr_arg)
		return (ft_error(4, (char*[]){INVALID_PARAMS_NBR, unit->tokens[index].token
						, AT_LINE, ft_static_ulltoa(unit->line_nbr)}, 0));
	i = index + 1;
	while (i < unit->tokens_nbr)
	{
		if (!(unit->tokens[i].token_content.param.param_type
			& op_tab[unit->tokens[index].token_content.opcode - 1].arg_type[i - index - 1]))
			return (ft_error(4, (char*[]){INVALID_PARAM_TYPE, unit->tokens[i].token
					, AT_LINE, ft_static_ulltoa(unit->line_nbr)}, 0));
		i++;
	}
	return (1);
}
