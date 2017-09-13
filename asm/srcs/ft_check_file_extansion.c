/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_extansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 01:17:28 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/13 10:06:01 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_check_file_extansion(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 2)
		ft_put_asm_usage(filename);
	len -= 2;
	if (!ft_strequ(filename + len, ASM_FILE_EXTENSION))
	{
		ft_error(2, (char*[]){INVALID_FILE_EXTENSION, filename}, EXIT_FAILURE);
		ft_put_asm_usage(NULL);
	}
}
