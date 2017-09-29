/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_dk_location.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 22:53:05 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/18 22:56:08 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline t_dk_location	ft_set_dk_location(t_dk_info *dk_info, uint64_t line
										, uint64_t column, uint64_t token_nbr)
{
	t_dk_location	dk_location;

	dk_location = (t_dk_location){line, column, token_nbr};
	dk_info->location = dk_location;
	return (dk_location);
}
