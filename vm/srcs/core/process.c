/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 23:59:18 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 02:34:45 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*pc_new(t_reg number)
{
	t_process	*npc;

	npc = ft_salloc(sizeof(t_process));
	ft_bzero(npc, sizeof(t_process));
	npc->reg[0] = number;
	npc->flags = 0;
	npc->last_live = 1;
	return (npc);
}

void		pc_push(t_process **root, t_process *pc)

	if (!*root)
		return ((void)(*root = pc));
	pc->next = *root;
	*root = pc;
}

void		pc_remove(t_process **root, t_process *pc)
{
	t_process *ptr;

	ptr = *root;
	if (*root == pc)
	{
		*root = (*root)->next;
		free(ptr);
		return ;
	}
	while (ptr->next)
	{
		if (ptr->next == pc)
		{
			ptr->next = pc->next;
			free(pc);
			return ;
		}
		ptr = ptr->next;
	}
}

void		pc_clear(t_process *root)
{
	t_process	*tmp;

	while (root)
	{
		tmp = root;
		root = root->next;
		free(tmp);
	}
}
