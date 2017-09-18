/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_abort_on_dk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 22:58:35 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/18 22:59:26 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint8_t	*ft_get_abort_on_dk(void)
{
	static uint8_t	abort_on_dk = 0;

	return (&abort_on_dk);
}
