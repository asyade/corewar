/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 06:51:15 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdarg.h>
#include <fcntl.h>

char		*ptstr(t_byte type)
{
	if (type == T_REG)
		return ("T_REG");
	else if (type == T_DIR)
		return ("T_DIR");
	else if (type == T_IND)
		return ("T_IND");
	return ("T_UNDEF");
}

char		*reg_str(t_int32 inst[6], int i)
{
	static char	st[2] = (char[2]) { '\0', '\0' };

	st[0] = '\0';
	st[1] = '\0';
	if (i == 1 && IP1(inst[1]) == T_REG)
		st[0] = 'r';
	if (i == 2 && IP2(inst[1]) == T_REG && inst[0] != 3)
		st[0] = 'r';
	if (i == 3 && IP3(inst[1]) == T_REG)
		st[0] = 'r';
	if (i == 4 && IP4(inst[1]) == T_REG)
		st[0] = 'r';
	return (st);
}

char		*dump_parametters(t_vm *vm, t_process *pc, uint32_t nbr_param)
{
	const uint8_t	*print_type[OP_NBR] = {PF1, PF2, PF3, PF4, PF5, PF6,
PF7, PF8, PF9, PF10, PF11, PF12, PF13, PF14, PF15, PF16};
	static char		buff[1024];
	char			*bptr;
	uint32_t		i;

	bptr = buff;
	*bptr = '\0';
	i = 0;
	if (nbr_param == 0)
		ft_sprintf(buff, " %d", pc->inst[1]);
	while (i < nbr_param)
	{
		if (!print_type[pc->inst[0] - 1][i])
			bptr += ft_sprintf(bptr, " %s%d",
reg_str(pc->inst, i + 1), pc->inst[i + 2]);
		else if (print_type[pc->inst[0] - 1][i] == 1)
			bptr += ft_sprintf(bptr, " %d", param_dirval(pc, i + 1));
		else
			bptr += ft_sprintf(bptr, " %d",
param_idxval(vm, pc, i + 1));
		i++;
	}
	return (buff);
}
