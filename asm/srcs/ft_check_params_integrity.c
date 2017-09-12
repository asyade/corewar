/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_params_integrity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 04:27:52 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/12 06:41:20 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

inline uint32_t			ft_get_instruction_params(char *line, char **params)
{
	char		*tmp;
	size_t		i;
	uint32_t	nbr_params;

	i = 0;
	while (ft_strchr(CHARSET_WHITESPACES, line[i]))
		i++;
	if (!line[i])
		return (0);
	params[0] = line + i;
	nbr_params = 1;
	while ((tmp = ft_strchr(line, SEPARATOR_CHAR)) && nbr_params <= MAX_NBR_PARAMS)
	{
		i = (size_t)(tmp - line);
		while (ft_strchr(CHARSET_WHITESPACES, line[i]))
			i++;
		params[nbr_params] = line + i;
		nbr_params++;
	}
	return (nbr_params);
}

inline int32_t			ft_check_params_integrity(int32_t instruction_index
										, char *line)
{
	char		*params_nbrs[] = {"1", "2", "3"};
	char		*params[3];
	uint32_t	nbr_params;
	uint32_t	i;
	t_arg_type	tmp;

	if ((nbr_params = ft_get_instruction_params(line, params)) > MAX_NBR_PARAMS)
		return (ft_error(2, (char*[]){INVALID_PARAMS_NBR, op_tab[instruction_index].name}, 0));
	i = 0;
	while (i < nbr_params)
	{
		tmp = ft_get_instruction_param_type(params[i]);
		if (!(tmp & op_tab[instruction_index].arg_type[i]))
			return (ft_error(2, (char*[]){INVALID_PARAM_TYPE, params_nbrs[i]}, 0));
		i++;
	}
	return (1);
}
