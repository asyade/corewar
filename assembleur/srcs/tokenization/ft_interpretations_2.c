/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpretations_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:22:19 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:22:39 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int32_t	ft_interpret_comment(t_semantic_unit *unit, uint64_t token_index
							, t_token *token, t_bin_buffer *bin)
{
	(void)unit;
	(void)token_index;
	(void)token;
	(void)bin;
	return (1);
}

int32_t	ft_interpret_content(t_semantic_unit *unit, uint64_t token_index
							, t_token *token, t_bin_buffer *bin)
{
	(void)unit;
	(void)token_index;
	(void)token;
	(void)bin;
	return (1);
}

int32_t	ft_interpret_param(t_semantic_unit *unit, uint64_t token_index
							, t_token *token, t_bin_buffer *bin)
{
	(void)unit;
	(void)bin;
	if (token_index < 1)
		return (ft_diagnostic(&g_dk_info, INVALID_EXPRESSION, 0));
	token->token_content.param.param_type = ft_get_instruction_param_type(
		token->token);
	return (1);
}

int32_t	ft_interpret_label(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin)
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
		return (ft_diagnostic(&g_dk_info, LABEL_REDEFINITION, 0));
	if (!(tmp = (t_list*)ft_memalloc(sizeof(t_list)))
		|| !(label = (t_label*)ft_memalloc(sizeof(t_label))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	label->name = token->token;
	label->instruction_index = *ft_get_instruction_count();
	label->relative_address = bin->offset;
	tmp->content = label;
	ft_lstadd(lst, tmp);
	return (1);
}
