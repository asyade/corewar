/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpretations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:42:16 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:24:13 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int32_t			ft_interpret_err(t_semantic_unit *unit
				, uint64_t token_index, t_token *token, t_bin_buffer *bin)
{
	(void)token_index;
	(void)bin;
	(void)unit;
	if (token)
		ft_diagnostic(&g_dk_info, INVALID_EXPRESSION, 0);
	return (0);
}

int32_t			ft_interpret_instruction(
					t_semantic_unit __attribute__((unused)) *unit
					, uint64_t token_index, t_token *token, t_bin_buffer *bin)
{
	static const char	*opcodes[] = {"live", "ld", "st", "add", "sub",
		"and", "or", "xor", "zjmp", "ldi",
		"sti", "fork", "lld", "lldi", "lfork",
		"aff"};
	uint32_t			i;

	i = 0;
	(void)bin;
	if (token_index != 0 && token_index != 1)
		return (ft_diagnostic(&g_dk_info, ILLEGAL_USE_INSTRUCTION, 0));
	while (i < sizeof(opcodes) / sizeof(char*))
	{
		if (ft_strequ(token->token, opcodes[i]))
		{
			token->token_content.opcode = g_op_tab[i].opcode;
			return (1);
		}
		i++;
	}
	return (ft_diagnostic(&g_dk_info, INVALID_INSTRUCTION, 0));
}

int32_t			ft_interpret_name(t_semantic_unit *unit
						, uint64_t token_index
						, t_token *token, t_bin_buffer *bin)
{
	(void)unit;
	(void)token_index;
	(void)token;
	(void)bin;
	return (1);
}

inline int32_t	ft_interpret_tokens(t_semantic_unit *unit
											, t_bin_buffer *bin)
{
	static const	t_f_interpret_token	interpretations[] =
	{	&ft_interpret_err,
		&ft_interpret_instruction,
		&ft_interpret_name,
		&ft_interpret_comment,
		&ft_interpret_content,
		&ft_interpret_param,
		&ft_interpret_label};
	uint64_t							i;

	i = 0;
	while (i < unit->tokens_nbr)
	{
		g_dk_info.content = unit->tokens[i].token;
		g_dk_info.location.len = unit->tokens[i].len;
		g_dk_info.location.column = unit->tokens[i].column;
		if (!(interpretations[unit->tokens[i].token_type](unit, i
											, &unit->tokens[i], bin)))
			ft_diagnostic(&g_dk_info, INVALID_EXPRESSION, 0);
		i++;
	}
	return (1);
}
