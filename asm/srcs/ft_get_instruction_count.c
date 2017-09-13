/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_instruction_count.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 04:09:43 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/13 10:03:05 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint64_t	*ft_get_instruction_count(void)
{
	static uint64_t	instruction_count = 0;

	return (&instruction_count);
}
