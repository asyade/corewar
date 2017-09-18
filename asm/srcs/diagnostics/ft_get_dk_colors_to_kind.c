/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dk_colors_to_kind.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 22:45:10 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/19 00:50:37 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline t_dk_color	ft_get_dk_colors_to_kind(t_dk_kind kind)
{
	static const t_dk_color	colors[DK_LAST_KIND + 1] = {
		{RESET, RESET, RESET},
		{RED_FOND, BACK_RESET, BOLD},
		{MAGENTA_FOND, BACK_RESET, BOLD},
		{RED_FOND, BACK_WHITE, UNDERLINE},
		{RESET, RESET, RESET},
	};

	if (kind >= DK_LAST_KIND || kind <= DK_UNKNOWN)
		ft_error_exit(2, (char*[]){"Invalid kind provided to "
					, (char*)(uintptr_t)__func__}, EXIT_FAILURE);
	return (colors[kind]);
}
