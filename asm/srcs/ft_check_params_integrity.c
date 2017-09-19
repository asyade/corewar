/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_params_integrity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 04:27:52 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/19 03:36:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline int32_t	ft_check_params_integrity(t_semantic_unit *unit, uint64_t index)
{
	uint64_t	i;

	g_dk_info.content = unit->tokens[index].token;
	g_dk_info.location.column = unit->tokens[index].column;
	g_dk_info.location.len = unit->tokens[index].len;
	if (unit->tokens_nbr - index - 1 > op_tab[unit->tokens[index].token_content.opcode - 1].nbr_arg)
		return (ft_diagnostic(&g_dk_info, INVALID_PARAMS_NBR, 0));
	i = index + 1;
	while (i < unit->tokens_nbr)
	{
		g_dk_info.content = unit->tokens[i].token;
		g_dk_info.location.column = unit->tokens[i].column;
		g_dk_info.location.len = unit->tokens[index].len;
		if (!(unit->tokens[i].token_content.param.param_type
			& op_tab[unit->tokens[index].token_content.opcode - 1].arg_type[i - index - 1]))
			return (ft_diagnostic(&g_dk_info, INVALID_PARAM_TYPE, 0));
		i++;
	}
	return (1);
}
