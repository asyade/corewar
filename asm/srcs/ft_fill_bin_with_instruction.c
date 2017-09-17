/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_bin_with_instruction.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:50:15 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/17 22:53:13 by sclolus          ###   ########.fr       */
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
		size += unit->tokens[i].token_content.param.size;
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

static inline void			ft_fill_buffer_with_params(uint8_t *buffer, t_semantic_unit *unit
													   , uint64_t index, uint64_t bin_offset)
{
	uint64_t	i;
	uint64_t	offset;

	i = index + 1;
	offset = 0;
	while (i < unit->tokens_nbr)
	{
		unit->tokens[i].relative_address = bin_offset + offset;
		ft_memcpy(buffer + offset, unit->tokens[i].token_content.param.content.raw_value
				, unit->tokens[i].token_content.param.size);
		offset += unit->tokens[i].token_content.param.size;
		i++;
	}
}

void	ft_fill_bin_with_instruction(t_semantic_unit *unit, uint64_t index
										, t_bin_buffer *bin)
{
	static uint8_t	buffer[14];
	uint64_t		instruction_size;
	uint64_t		encoding_byte;

	unit->relative_address = bin->offset;
	encoding_byte = op_tab[unit->tokens[index].token_content.opcode - 1].octal_code;
	instruction_size = 1 + encoding_byte + ft_get_params_size(unit, index);
	if (instruction_size + bin->offset > bin->capacity)
		ft_error_exit(1, (char*[]){"champ size too big"}, EXIT_FAILURE);
	buffer[0] = unit->tokens[index].token_content.opcode;
	if (encoding_byte)
		buffer[1] = ft_make_encoding_byte(ft_get_arg_type_buffer(unit, index)
		, op_tab[unit->tokens[index].token_content.opcode - 1].nbr_arg);
	ft_fill_buffer_with_params(buffer + 1 + encoding_byte, unit, index, bin->offset + 1 + encoding_byte);
	ft_memcpy(bin->buffer + bin->offset, buffer, instruction_size);
	bin->offset += instruction_size;
}
