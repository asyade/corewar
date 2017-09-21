/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bin_filename.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 06:43:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:39:23 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline char	*ft_get_bin_filename(char *filename)
{
	char		*cpy;
	uint64_t	len;

	len = ft_strlen(filename) - 1;
	if (!(cpy = ft_strndup(filename, len + 3)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	while (len > 0)
	{
		if (filename[len] == '.')
			break ;
		len--;
	}
	ft_memcpy(cpy + len, BIN_FILE_EXTENSION, sizeof(BIN_FILE_EXTENSION));
	return (cpy);
}
