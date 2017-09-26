/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:05:18 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	fill_line(char *buff, t_byte *ptr, int n)
{
	while (n--)
	{
		*buff++ = DUMP_BASE[*ptr / 16];
		*buff++ = DUMP_BASE[*ptr++ % 16];
		*buff++ = ' ';
	}
	*buff = '\0';
}

static void	dump_line(t_byte *ptr, t_vptr v, int n)
{
	char	buff[DUMP_LSIZE];

	fill_line(buff + sprintf(buff, "0x%4.4x : ", (unsigned)v), ptr, n);
	printf("%s\n", buff);
}

void		dump(t_vm *vm)
{
	t_vptr	curr;
	char	buff[3];

	curr = 0;
	while (curr < MEM_SIZE)
	{
		dump_line(vm->memory.mem + curr, curr, DUMP_OPL);
		curr += DUMP_OPL;
	}
	if (vm->params->flag & P_DUMPREP)
	{
		vm->params->dump = vm->params->basedump;
		read(0, buff, 1);
	}
	else
		exit(0);
}
