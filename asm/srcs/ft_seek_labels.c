/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seek_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 09:58:05 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:21:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	ft_assign_label_value(t_token *token, t_bin_buffer *bin
										  , t_semantic_unit *unit)
{
	t_list			*label;
	uint64_t		i;

	i = 0;
	g_dk_info.content = token->token;
	g_dk_info.location.line = unit->line_nbr;
	g_dk_info.line = unit->line;
	g_dk_info.location.column = token->column;
	g_dk_info.location.len = token->len;
	while (token->token[i] != ':' && token->token[i])
		i++;
	if (!token->token[i] || !token->token[i + 1])
		ft_diagnostic(&g_dk_info, UNKNOWN_LABEL_INVOCATION, 0);
	if (!(ft_check_label_integrity(token->token + i + 1)))
		ft_diagnostic(&g_dk_info, INVALID_LABEL_CHARS, 0);
	i++;
	if (!(label = ft_find_label(token->token + i, *ft_get_label_lst())))
		ft_diagnostic(&g_dk_info, UNKNOWN_LABEL_INVOCATION, 0);
	if (token->token_content.param.size == 2)
		*((uint16_t*)(void*)(bin->buffer + token->relative_address)) =
			ft_bswap_u16((uint16_t)(((t_label*)label->content)->relative_address - unit->relative_address));
	else if (token->token_content.param.size == 4)
		*((uint32_t*)(void*)(bin->buffer + token->relative_address)) =
			ft_bswap_u32((uint32_t)(((t_label*)label->content)->relative_address - unit->relative_address));
}

static inline void	ft_cleanup_labels(t_list **labels)
{
	t_list	*label_lst;
	t_list	*tmp;

	label_lst = *labels;
	tmp = NULL;
	while (label_lst)
	{
		free(label_lst->content);
		tmp = label_lst;
		label_lst = label_lst->next;
		free(tmp);
	}
	*labels = NULL;
}

void				ft_seek_labels(t_list *unit_lst, t_bin_buffer *bin)
{
	uint64_t		i;
	t_semantic_unit	*tmp;

	while (unit_lst)
	{
		i = 0;
		tmp = unit_lst->content;
		while (i < tmp->tokens_nbr)
		{
			if (tmp->tokens[i].token_type == PARAM
				&& tmp->tokens[i].token_content.param.label_to_seek)
				ft_assign_label_value(tmp->tokens + i, bin, tmp);
			i++;
		}
		unit_lst = unit_lst->next;
	}
	ft_cleanup_labels(ft_get_label_lst());
}
