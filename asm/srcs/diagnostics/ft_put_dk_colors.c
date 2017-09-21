/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_dk_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:31:15 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:32:03 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline void			ft_put_dk_colors(t_dk_color colors)
{
	ft_putstr_fd(colors.font, 2);
	ft_putstr_fd(colors.back, 2);
	ft_putstr_fd(colors.style, 2);
}

inline void			ft_dk_colors_reset(void)
{
	ft_putstr_fd(RESET, 2);
}
