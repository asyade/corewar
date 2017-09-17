/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_instruction_param_type.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 06:15:13 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/17 14:55:59 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline t_arg_type	ft_get_instruction_param_type(char *param)
{
	if (param[0] == 'r' && ft_isdigit(param[1]))
		return (T_REG);
	else if (param[0] == DIRECT_CHAR && param[1])
	{
		if (param[1] == LABEL_CHAR)
			return (T_LAB | T_DIR);
		return (T_DIR);
	}
	else
	{
		if (param[1] == LABEL_CHAR)
			return (T_LAB | T_IND);
		return (T_IND);
	}
}
