/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_label_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 07:13:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 20:42:18 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline t_list	*ft_find_label(char *name, t_list *label_lst)
{
	while (label_lst)
	{
		if (ft_strequ(name, (char*)((t_label*)label_lst->content)->name))
			return (label_lst);
		label_lst = label_lst->next;
	}
	return (NULL);
}

t_list			**ft_get_label_lst(void)
{
	static t_list	*label_lst = NULL;

	return (&label_lst);
}
