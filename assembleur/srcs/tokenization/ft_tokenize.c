/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 04:01:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:24:14 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline uint64_t	ft_adjust_dk_columns(char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i] && ft_strchr(CHARSET_SEPARATORS, line[i]))
		i++;
	return (i);
}

static inline void		ft_assign_tokens_data(t_semantic_unit *unit
											, char **tokens)
{
	uint64_t	i;
	uint64_t	column_add;

	i = 0;
	column_add = ft_adjust_dk_columns(g_dk_info.line);
	while (tokens[i] && i < MAX_NBR_TOKEN)
	{
		unit->tokens[i].token = tokens[i];
		unit->tokens[i].len = ft_strlen(tokens[i]);
		unit->tokens[i].column = (uint64_t)(uintptr_t)tokens[i]
			- (uintptr_t)tokens[0] + column_add;
		i++;
	}
	unit->tokens_nbr = i;
}

t_semantic_unit			*ft_tokenize(char *line, t_bin_buffer *bin)
{
	t_semantic_unit	*semantic_unit;
	char			**tokens;

	if (
	!(semantic_unit = (t_semantic_unit*)ft_memalloc(sizeof(t_semantic_unit))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	semantic_unit->line = line;
	semantic_unit->line_nbr = *ft_get_instruction_count();
	tokens = ft_split(line, CHARSET_SEPARATORS);
	ft_assign_tokens_data(semantic_unit, tokens);
	ft_assign_tokens_type(semantic_unit);
	ft_interpret_tokens(semantic_unit, bin);
	semantic_unit->relative_address = bin->offset;
	free(tokens);
	return (semantic_unit);
}
