/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bin_integrity.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 21:20:54 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/19 00:43:12 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline void	ft_check_bin_integrity(t_bin_buffer *bin)
{
	if (!bin->name_flag)
		ft_error_exit(3, (char*[]){"Error: ", UNAMED_BIN_FILE}, EXIT_FAILURE);
	if (!bin->comment_flag)
		ft_error(2, (char*[]){WARNING, NO_COMMENT_DEFINED}, 0);
	if (!bin->offset)
		ft_error_exit(2, (char*[]){"Error: ", EMPTY_TEXT}, EXIT_FAILURE);
}
