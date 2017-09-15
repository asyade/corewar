/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_params_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:52:32 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/15 14:15:48 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int32_t	ft_get_reg_value(t_token *token)
{
	uint32_t	i;
	uint8_t		tmp_value;

	i = 1;
	while (token->token[i])
	{
		if (!ft_strchr(CHARSET_DECIMAL, token->token[i]))
			return (ft_error(2, (char*[]){INVALID_EXPRESSION, token->token}, 0));
		i++;
	}
	if ((tmp_value = (uint8_t)ft_atoi(token->token + 1)) > REG_NUMBER)
		return (ft_error(2, (char*[]){INVALID_REG_NUMBER, token->token}, 0));
	token->token_content.param.content.reg_value = tmp_value;
	return (1);
}

static int32_t	ft_get_dir_value(t_token *token)
{
	t_list		*label;
	int32_t		direct_value;
	uint32_t	i;

	if (token->token[0] && token->token[1] == LABEL_CHAR)
	{
		if (ft_strlen(token->token) < 3
			|| !(label = ft_find_label(token->token + 2, *ft_get_label_lst())))
			return (ft_error(2, (char*[]){UNKOWN_LABEL_INVOCATION, token->token}, 0));
		direct_value = (int32_t)((t_label*)label->content)->relative_address;
	}
	else
	{
		i = 1;
		while (token->token[i])
		{
			if (!ft_strchr(CHARSET_DECIMAL, token->token[i]))
				return (ft_error(2, (char*[]){INVALID_EXPRESSION, token->token}, 0));
			i++;
		}
		direct_value = ft_atoi(token->token + 1);
	}
	token->token_content.param.content.direct_value = direct_value;
	return (1);
}

static int32_t	ft_get_ind_value(t_token *token)
{
	t_list		*label;
	int16_t		indirect_value;
	uint32_t	i;

	if (token->token[0] == LABEL_CHAR)
	{
		if (ft_strlen(token->token) < 2
			|| !(label = ft_find_label(token->token + 1, *ft_get_label_lst())))
			return (ft_error(2, (char*[]){UNKOWN_LABEL_INVOCATION, token->token}, 0));
		indirect_value = (int16_t)((t_label*)label->content)->relative_address;
	}
	else
	{
		i = 1;
		while (token->token[i])
		{
			if (!ft_strchr(CHARSET_DECIMAL, token->token[i]))
				return (ft_error(2, (char*[]){INVALID_EXPRESSION, token->token}, 0));
			i++;
		}
		indirect_value = (int16_t)ft_atoi(token->token + 1);
	}
	token->token_content.param.content.indirect_value = indirect_value;
	return (1);
}

int32_t			ft_get_param_value(t_token *token)
{
	static const	t_f_param_value	param_get_value[] =
	{{&ft_get_reg_value, T_REG, {0}},
	{&ft_get_dir_value, T_DIR, {0}},
	{&ft_get_ind_value, T_IND, {0}}};
	uint32_t						i;

	i = 0;
	while (i < sizeof(param_get_value) / sizeof(t_f_param_value))
	{
		if (token->token_content.param.param_type == param_get_value[i].id)
			return (param_get_value[i].f(token));
		i++;
	}
	return (0);
}

int32_t			ft_get_params_value(t_semantic_unit *unit
									, uint64_t index)
{
	uint64_t	i;

	i = index + 1;
	while (i < unit->tokens_nbr)
	{
		if (!ft_get_param_value(unit->tokens + i))
			return (0);
		i++;
	}
	return (1);
}
