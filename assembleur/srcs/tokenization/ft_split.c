/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 05:24:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:48:46 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline static size_t	ft_count_tokens(char *str, size_t len)
{
	size_t		i;
	size_t		nbr_tokens;

	i = 0;
	nbr_tokens = 0;
	while (i < len)
	{
		while (!str[i] && i < len)
			i++;
		if (i < len)
			nbr_tokens++;
		while (str[i] && i < len)
			i++;
	}
	return (nbr_tokens);
}

static inline char		**ft_assign_tokens(char **tokens, size_t len
										, size_t nbr_tokens
										, char *str)
{
	size_t	i;
	size_t	u;

	i = 0;
	u = 0;
	if (!nbr_tokens)
		free(str);
	while (u < nbr_tokens)
	{
		while (!str[i] && i < len)
			i++;
		if (i < len)
			tokens[u++] = str + i;
		while (str[i] && i < len)
			i++;
	}
	return (tokens);
}

char					**ft_split(char *str, char *separators)
{
	char		**tokens;
	char		*tmp;
	size_t		len;
	size_t		i;
	size_t		nbr_tokens;

	len = ft_strlen(str);
	if (!(tmp = ft_strdup(str)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	i = 0;
	nbr_tokens = 0;
	while (i < len)
	{
		if (ft_strchr(separators, tmp[i]) && !nbr_tokens)
			tmp[i] = '\0';
		if (tmp[i] == '"')
			nbr_tokens ^= 1;
		i++;
	}
	nbr_tokens = ft_count_tokens(tmp, len);
	if (!(tokens = (char**)malloc(sizeof(char*) * (nbr_tokens + 1))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	tokens[nbr_tokens] = NULL;
	return (ft_assign_tokens(tokens, len, nbr_tokens, tmp));
}
