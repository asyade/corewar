/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpretations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:42:16 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/14 12:07:20 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int32_t	ft_interpret_err(t_semantic_unit *unit, uint64_t token_index, t_token *token)
{
	(void)token_index;
	if (token) //gcc trick
		ft_error_exit(4, (char*[]){"Invalid token: ", token->token, " at line: "
				, ft_static_ulltoa(unit->line_nbr)}, EXIT_FAILURE);
	// leaks at ft_itoa
	return (0);
}

int32_t	ft_interpret_instruction(t_semantic_unit *unit, uint64_t token_index, t_token *token)
{
	static const char	*opcodes[] =
		{"live", "ld", "st", "add", "sub",
		"and", "or", "xor", "zjmp", "ldi",
		"sti","fork","lld","lldi","lfork",
		"aff"};
	uint32_t	i;

	i = 0;
	if (token_index != 0 && token_index != 1)
		return (ft_error(4, (char*[]){ILLEGAL_USE_INSTRUCTION, token->token
					, AT_LINE, ft_static_ulltoa(unit->line_nbr)}, 0));
	while (i < sizeof(opcodes) / sizeof(char*))
	{
		if (ft_strequ(token->token, opcodes[i]))
		{
			token->token_content.opcode = op_tab[i].opcode;
			return (1);
		}
		i++;
	}
	return (ft_error(4, (char*[]){INVALID_INSTRUCTION, token->token
					, AT_LINE, ft_static_ulltoa(unit->line_nbr)}, 0));
}

int32_t	ft_interpret_name(t_semantic_unit *unit, uint64_t token_index, t_token *token)
{
	(void)unit;
	(void)token_index;
	(void)token;
	return (1); // ??
}

int32_t	ft_interpret_comment(t_semantic_unit *unit, uint64_t token_index, t_token *token)
{
	(void)unit;
	(void)token_index;
	(void)token;
	return (1); // ??
}

int32_t	ft_interpret_content(t_semantic_unit *unit, uint64_t token_index, t_token *token)
{
	(void)unit;
	(void)token_index;
	(void)token;
	return (1);
}

int32_t	ft_interpret_param(t_semantic_unit *unit, uint64_t token_index, t_token *token)
{
	if (token_index < 1)
		return (ft_error(4, (char*[]){ILLEGAL_PARAM_INVOCATION, token->token
					, AT_LINE, ft_static_ulltoa(unit->line_nbr)}, 0));
	token->token_content.param.param_type = ft_get_instruction_param_type(token->token);
	return (1);
}

int32_t	ft_interpret_label(t_semantic_unit *unit, uint64_t token_index, t_token *token)
{
	t_list	**lst;
	t_list	*tmp;
	t_label	*label;

	(void)unit;
	(void)token_index;
	(void)token;
	lst = ft_get_label_lst();
	token->token[ft_strlen(token->token) - 1] = '\0';
	if (ft_find_label(token->token, *lst))
		return (ft_error(4, (char*[]){LABEL_REDEFINITION, token->token
					, AT_LINE, ft_static_ulltoa(unit->line_nbr)}, 0));
	if (!(tmp = ft_lstnew(0, 0))
		|| !(label = (t_label*)ft_memalloc(sizeof(t_label))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	label->name = token->token; // ?
	label->instruction_index = *ft_get_instruction_count();
	tmp->content = label;
	ft_lstadd(lst, tmp);
	return (1); // ??
}