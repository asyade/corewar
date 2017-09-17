/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_bin_with_instruction.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:50:15 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/15 23:49:19 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline uint64_t		ft_get_params_size(t_semantic_unit *unit, uint64_t index)
{
	uint64_t	i;
	uint64_t	size;

	i = index + 1;
	size = 0;
	while (i < unit->tokens_nbr)
	{
		if (unit->tokens[i].token_content.param.param_type == T_REG)
			size += 1;
		else if (unit->tokens[i].token_content.param.param_type == T_IND)
			size += 2;
		else
			size += 4;
		i++;
	}
	return (size);
}

static inline t_arg_type	*ft_get_arg_type_buffer(t_semantic_unit *unit
													, uint64_t index)
{
	static t_arg_type	arg_types[4];
	uint64_t			i;

	i = index + 1;
	while (i < unit->tokens_nbr)
	{
		arg_types[i - index - 1] = unit->tokens[i].token_content.param.param_type;
		i++;
	}
	return (arg_types);
}

static inline void			ft_fill_buffer_with_params(uint8_t *buffer, t_semantic_unit *unit, uint64_t index)
{
	uint64_t	i;
	uint64_t	offset;

	i = index + 1;
	offset = 2;
	while (i < unit->tokens_nbr)
	{
		if (unit->tokens[i].token_content.param.param_type == T_REG)
		{
			ft_memcpy(buffer + offset, &unit->tokens[i].token_content.param.content.reg_value, T_REG_CODE_SIZE);
			offset += 1;
		}
		else if (unit->tokens[i].token_content.param.param_type == T_IND)
		{
			ft_memcpy(buffer + offset, &unit->tokens[i].token_content.param.content.indirect_value, T_IND_CODE_SIZE);
			offset += 2;
		}
		else
		{
			ft_memcpy(buffer + offset, &unit->tokens[i].token_content.param.content.direct_value, T_DIR_CODE_SIZE);
			offset += 4;
		}
		i++;
	}
}

void	ft_fill_bin_with_instruction(t_semantic_unit *unit, uint64_t index
										, t_bin_buffer *bin)
{
	static uint8_t	buffer[14];
	uint64_t		instruction_size;


	instruction_size = 1 + 1 + ft_get_params_size(unit, index);
	if (instruction_size + bin->offset >= bin->capacity)
		ft_error_exit(1, (char*[]){"champ size too big"}, EXIT_FAILURE);
	buffer[0] = unit->tokens[index].token_content.opcode;
	buffer[1] = ft_make_encoding_byte(ft_get_arg_type_buffer(unit, index)
		, op_tab[unit->tokens[index].token_content.opcode - 1].nbr_arg);
	ft_fill_buffer_with_params(buffer, unit, index);
	ft_memcpy(bin->buffer + bin->offset, buffer, instruction_size);
	bin->offset += instruction_size;
}
