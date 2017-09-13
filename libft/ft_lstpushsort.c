/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 04:51:12 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/12 04:51:16 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushsort(t_list **root, t_list *elem,
		int (*cmp)(t_list *, t_list *))
{
	t_list	*tmp;

	if (!(tmp = *root))
		return (*root = elem);
	if (cmp(tmp, elem) >= 0)
	{
		elem->next = tmp;
		return (*root = elem);
	}
	while (tmp->next)
	{
		if (cmp(tmp->next, elem) >= 0)
		{
			elem->next = tmp->next;
			return (tmp->next = elem);
		}
		tmp = tmp->next;
	}
	return (tmp->next = elem);
}
