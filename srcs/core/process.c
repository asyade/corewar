/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 23:59:18 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/15 00:43:59 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*pc_new(t_reg number)
{
	t_process	*npc;

	npc = ft_salloc(sizeof(t_process));
	ft_bzero(npc, sizeof(t_process));
	npc->reg[0] = number;
	return (npc);
}

void		pc_push(t_process **root, t_process *pc)
{
	if (!*root)
		return ((void)(*root = pc));
	pc->next = *root;
	*root = pc;
}

void		pc_remove(t_process **root, t_process *pc)
{
	t_process	*fptr;

	fptr = pc;
	if (*root == pc)
	{
		*root = pc->next;
		free(fptr);
		return ;
	}
	while (fptr->next)
	{
		if (fptr->next == pc)
		{
			fptr->next = pc->next;
			free(fptr);
			return ;
		}
		fptr = fptr->next;
	}
}