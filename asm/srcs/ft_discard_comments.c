/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_discard_comments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 04:15:10 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/13 10:08:33 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline void	ft_discard_comments(char *line)
{
	char	*tmp;

	if (!(tmp = ft_strchr(line, COMMENT_CHAR)))
		return ;
	*tmp = '\0';
}
