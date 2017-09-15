/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 04:01:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/15 12:18:56 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void		ft_assign_tokens_data(t_semantic_unit *unit
											, char **tokens)
{
	uint64_t	i;

	i = 0;
	while (tokens[i] && i < MAX_PARAMS_NBR)
	{
		unit->tokens[i].token = tokens[i];
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
	static const t_f_lexing		lexing_checks[] =
		{&ft_lex_is_instruction, &ft_lex_is_label, &ft_lex_is_name
		, &ft_lex_is_comment, &ft_lex_is_content, &ft_lex_is_param};

	i = 0;
	while (i < sizeof(lexing_checks) / sizeof(t_f_lexing))
	{
		if (lexing_checks[i](unit->tokens[token_index].token))
		{
			unit->tokens[token_index].token_type = token_types[i];
//			printf("token: %s is of type: %d\n", unit->tokens[token_index].token, i);
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
		ft_assign_token_type(unit, i);
		i++;
	}
}

typedef int32_t (*t_f_interpret_token)(t_semantic_unit *, uint64_t, t_token *);

static inline int32_t	ft_interpret_tokens(t_semantic_unit *unit)
{
	static const	t_f_interpret_token	interpretations[] =
	{	&ft_interpret_err,
		&ft_interpret_instruction,
		&ft_interpret_name,
		&ft_interpret_comment,
		&ft_interpret_content,
		&ft_interpret_param,
		&ft_interpret_label};
	uint64_t		i;

	i = 0;
	while (i < unit->tokens_nbr)
	{
		if (!(interpretations[unit->tokens[i].token_type](unit, i
												, &unit->tokens[i])))
		{
//			return (0);
			;
		}
		i++;
	}
	return (1);
}

t_semantic_unit			*ft_tokenize(char *line)
{
	t_semantic_unit	*semantic_unit;
	char			**tokens;

	if (!(semantic_unit
		= (t_semantic_unit*)ft_memalloc(sizeof(t_semantic_unit))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	semantic_unit->line = line;
	semantic_unit->line_nbr = *ft_get_instruction_count();
	tokens = ft_split(line, CHARSET_SEPARATORS);
	ft_assign_tokens_data(semantic_unit, tokens);
	ft_assign_tokens_type(semantic_unit);
	ft_interpret_tokens(semantic_unit);
	free(tokens);
	return (semantic_unit);
}
