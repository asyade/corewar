/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 04:01:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:48:22 by sclolus          ###   ########.fr       */
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

typedef int32_t	(*t_f_lexing)(char *);

static inline void		ft_assign_token_type(t_semantic_unit *unit
											, uint64_t token_index)
{
	uint32_t					i;
	static const t_token_type	token_types[] =
	{INSTRUCTION, LABEL, NAME, COMMENT, CONTENT, PARAM};
	static const t_f_lexing		lexing_checks[] = {&ft_lex_is_instruction
		, &ft_lex_is_label, &ft_lex_is_name
		, &ft_lex_is_comment, &ft_lex_is_content, &ft_lex_is_param};

	i = 0;
	while (i < sizeof(lexing_checks) / sizeof(t_f_lexing))
	{
		if (lexing_checks[i](unit->tokens[token_index].token))
		{
			unit->tokens[token_index].token_type = token_types[i];
			return ;
		}
		i++;
	}
	unit->tokens[token_index].token_type = ERR;
}

static inline void		ft_assign_tokens_type(t_semantic_unit *unit)
{
	uint64_t	i;

	i = 0;
	while (i < unit->tokens_nbr)
	{
		g_dk_info.content = unit->tokens[i].token;
		g_dk_info.location.len = unit->tokens[i].len;
		g_dk_info.location.column = unit->tokens[i].column;
		ft_assign_token_type(unit, i);
		i++;
	}
}

static inline int32_t	ft_interpret_tokens(t_semantic_unit *unit
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
