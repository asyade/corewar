/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 06:48:58 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	champ_swap(t_champ_describ *a, t_champ_describ *b)
{
	t_champ_describ tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		champs_sort(t_vm *vm)
{
	int		i;
	int		j;
	int		min;
	int		min_index;

	i = -1;
	while (++i < vm->params->count)
	{
		min = vm->params->champs[i].number;
		min_index = i;
		j = i;
		while (++j < vm->params->count)
		{
			if (vm->params->champs[j].number < min)
			{
				min = vm->params->champs[j].number;
				min_index = j;
			}
		}
		champ_swap(&vm->params->champs[i], &vm->params->champs[min_index]);
	}
}
