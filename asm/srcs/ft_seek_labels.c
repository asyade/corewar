/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seek_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 09:58:05 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/19 00:52:57 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	ft_assign_label_value(t_token *token, t_bin_buffer *bin
										  , t_semantic_unit *unit)
{
	t_list			*label;
	uint64_t		i;

	i = 0;
	while (token->token[i] != ':' && token->token[i])
		i++;
	if (!token->token[i])
		ft_error_exit(2, (char*[]){UNKNOWN_LABEL_INVOCATION, token->token}, EXIT_FAILURE);
	i++;
	if (!(label = ft_find_label(token->token + i, *ft_get_label_lst())))
		ft_error_exit(2, (char*[]){UNKNOWN_LABEL_INVOCATION, token->token}, EXIT_FAILURE);
	if (token->token_content.param.size == 2)
		*((uint16_t*)(void*)(bin->buffer + token->relative_address)) =
			ft_bswap_u16((uint16_t)(((t_label*)label->content)->relative_address - unit->relative_address));
	else if (token->token_content.param.size == 4)
		*((uint32_t*)(void*)(bin->buffer + token->relative_address)) =
			ft_bswap_u32((uint32_t)(((t_label*)label->content)->relative_address - unit->relative_address));
	else
		ft_error_exit(2, (char*[]){"Invalid invocation of label: "
					, token->token}, EXIT_FAILURE);
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
}
