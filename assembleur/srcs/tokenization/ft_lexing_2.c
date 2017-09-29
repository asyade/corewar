/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexing_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:50:39 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:15:00 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int32_t	ft_lex_is_comment(char *token)
{
	return (ft_strequ(token, ".comment"));
}

int32_t	ft_lex_is_content(char *token)
{
	return (*token == '"');
}

int32_t	ft_lex_is_param(char *token)
{
	(void)token;
	return (1);
}
