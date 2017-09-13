/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_asm_usage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 01:12:19 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/13 10:04:59 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

NORETURN	ft_put_asm_usage(char *str)
{
	if (str)
		ft_error(2, (char*[]){ASM_PARAM_ERROR, str}, 0);
	ft_error(1, (char*[]){ASM_USAGE}, 0);
	exit(EXIT_FAILURE);
}
