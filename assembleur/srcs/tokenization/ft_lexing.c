/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:29:48 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 21:52:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int32_t	ft_lex_is_label(char *token)
{
	uint64_t	i;

	i = 0;
	while (token[i])
	{
		if (!ft_strchr(LABEL_CHARS, token[i]) && token[i + 1])
			return (0);
		i++;
	}
	if (i > 0 && token[i - 1] == LABEL_CHAR)
		return (1);
	return (0);
}

int32_t	ft_lex_is_instruction(char *token)
{
	static const char	*opcodes[] =
	{"live", "ld", "st", "add", "sub",
	"and", "or", "xor", "zjmp", "ldi",
	"sti", "fork", "lld", "lldi", "lfork",
	"aff"};
	uint32_t			i;

	i = 0;
	if (!token)
		exit(EXIT_FAILURE);
	while (i < sizeof(opcodes) / sizeof(char*))
	{
		if (ft_strequ(token, opcodes[i]))
			return (1);
		i++;
	}
	return (0);
}

int32_t	ft_lex_is_name(char *token)
{
	return (ft_strequ(token, ".name"));
}
