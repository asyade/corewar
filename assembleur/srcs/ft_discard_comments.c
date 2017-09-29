/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_discard_comments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 04:15:10 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/22 23:15:11 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline void	ft_discard_comments(char *line)
{
	uint64_t	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(COMMENT_CHARS, line[i]))
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}
