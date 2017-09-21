/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_params_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:52:32 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 21:40:10 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int32_t		ft_get_reg_value(t_token *token, uint8_t opcode)
{
	uint8_t		tmp_value;

	(void)opcode;
	token->token_content.param.size = 1;
	g_dk_info.content = token->token;
	g_dk_info.location.column = token->column;
	g_dk_info.location.len = token->len;
	if (!(ft_is_token_decimal(token->token + 1)))
		return (ft_diagnostic(&g_dk_info, INVALID_EXPRESSION, 0));
	if ((tmp_value = (uint8_t)ft_atoi(token->token + 1)) > REG_NUMBER
		|| !tmp_value)
		return (ft_diagnostic(&g_dk_info, INVALID_REG_NUMBER, 0));
	token->token_content.param.content.reg_value = tmp_value;
	return (1);
}

static int32_t		ft_get_dir_value(t_token *token, uint8_t opcode)
{
	int32_t		direct_value;
	int16_t		indirect_value;

	g_dk_info.content = token->token;
	g_dk_info.location.column = token->column;
	g_dk_info.location.len = token->len;
	if (g_op_tab[opcode - 1].label_size)
		token->token_content.param.size = 2;
	else
		token->token_content.param.size = 4;
	if (token->token_content.param.param_type & T_LAB)
		return ((token->token_content.param.label_to_seek = 1));
	if (!(ft_is_token_decimal(token->token + 1)))
		return (ft_diagnostic(&g_dk_info, INVALID_EXPRESSION, 0));
	if (token->token_content.param.size == 2)
	{
		indirect_value = (int16_t)ft_atoi(token->token + 1);
		token->token_content.param.content.indirect_value =
			(int16_t)ft_bswap_u16((uint16_t)indirect_value);
	}
	else
	{
		direct_value = ft_atoi(token->token + 1);
		token->token_content.param.content.direct_value =
			(int32_t)ft_bswap_u32((uint32_t)direct_value);
	}
	return (1);
}

static int32_t		ft_get_ind_value(t_token *token, uint8_t opcode)
{
	int16_t		indirect_value;

	(void)opcode;
	g_dk_info.content = token->token;
	g_dk_info.location.column = token->column;
	g_dk_info.location.len = token->len;
	token->token_content.param.size = 2;
	if (token->token_content.param.param_type & T_LAB)
		return ((token->token_content.param.label_to_seek = 1));
	if (!(ft_is_token_decimal(token->token)))
		return (ft_diagnostic(&g_dk_info, INVALID_EXPRESSION, 0));
	if (token->token_content.param.size == 2)
	{
		indirect_value = (int16_t)ft_atoi(token->token);
		token->token_content.param.content.indirect_value
			= (int16_t)ft_bswap_u16((uint16_t)indirect_value);
	}
	return (1);
}

static int32_t			ft_get_param_value(t_token *token, uint8_t opcode)
{
	static const	t_f_param_value	param_get_value[] =
	{{&ft_get_reg_value, T_REG, {0}},
	{&ft_get_dir_value, T_DIR, {0}},
	{&ft_get_ind_value, T_IND, {0}}};
	uint32_t						i;

	i = 0;
	while (i < sizeof(param_get_value) / sizeof(t_f_param_value))
	{
		if (token->token_content.param.param_type & param_get_value[i].id)
			return (param_get_value[i].f(token, opcode));
		i++;
	}
	return (0);
}

int32_t				ft_get_params_value(t_semantic_unit *unit
									, uint64_t index)
{
	uint64_t	i;

	i = index + 1;
	while (i < unit->tokens_nbr)
	{
		if (!ft_get_param_value(unit->tokens + i
			, unit->tokens[index].token_content.opcode))
			return (0);
		i++;
	}
	return (1);
}
