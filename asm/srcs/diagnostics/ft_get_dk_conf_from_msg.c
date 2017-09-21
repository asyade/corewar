/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dk_conf_from_msg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 01:46:05 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:37:58 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline t_dk_conf	ft_get_dk_conf_from_msg(const char *msg)
{
	static const	t_dk_conf	confs[] =
	{{ASM_PARAM_ERROR, DK_ERROR, 0}, {ASM_USAGE, DK_ERROR, 0},
	{INVALID_FILE_EXTENSION, DK_ERROR, 0}, {INVALID_PARAMS_NBR, DK_ERROR, 1},
	{INVALID_PARAM_TYPE, DK_ERROR, 1}, {INVALID_INSTRUCTION, DK_ERROR, 1},
	{ILLEGAL_USE_INSTRUCTION, DK_ERROR, 1}
	, {ILLEGAL_PARAM_INVOCATION, DK_ERROR, 1}, {LABEL_REDEFINITION, DK_ERROR
	, 1}, {EXPECTED_EXPRESSION, DK_ERROR, 1}, {INVALID_EXPRESSION, DK_ERROR
	, 1}, {NAME_COMMENT_REDEFINITION, DK_WARNING, 1}, {NAME_TOO_LONG, DK_ERROR
	, 1}, {NAME_TOO_SHORT, DK_WARNING, 1}, {COMMENT_TOO_LONG, DK_ERROR, 1}
	, {INVALID_REG_NUMBER, DK_ERROR, 1}, {UNKNOWN_LABEL_INVOCATION, DK_ERROR
	, 1}, {CREATE_FILE_ERROR, DK_INTERNAL_ERROR, 0}, {UNAMED_BIN_FILE, DK_ERROR
	, 0}, {EMPTY_TEXT, DK_WARNING, 0}, {NO_COMMENT_DEFINED, DK_WARNING, 0}
	, {INVALID_LABEL_CHARS, DK_ERROR, 1}
	, {"Internal error: ", DK_INTERNAL_ERROR, 0}};
	uint64_t					i;

	i = 0;
	while (i < sizeof(confs) / sizeof(t_dk_conf))
	{
		if (ft_strequ(msg, confs[i].msg))
			return (confs[i]);
		i++;
	}
	return (confs[i - 1]);
}
