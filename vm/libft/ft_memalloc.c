/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:07:32 by sclolus           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/11/05 15:54:44 by sclolus          ###   ########.fr       */
=======
/*   Updated: 2017/09/28 22:40:34 by acorbeau         ###   ########.fr       */
>>>>>>> dump
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = (unsigned char*)malloc(size)))
<<<<<<< HEAD
		return (0);
	ft_bzero(mem, size);
	return (mem);
}
=======
	{
		ft_putendl_fd("exit: malloc() failure !", 1);
		exit(1);
	}
	ft_bzero(mem, size);
	return (mem);
}

void	*ft_salloc(size_t size)
{
	void	*mem;

	if (!(mem = (unsigned char*)malloc(size)))
	{
		ft_putendl_fd("exit: malloc() failure !", 2);
		exit(1);
	}
	return (mem);
}
>>>>>>> dump
