/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 02:08:01 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/18 15:39:40 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op    op_tab[OP_NBR] =
{
	//name		?	params								ID	Cycles	describ		PC IND_2/4
	{"live",	1, (t_arg_type[]){T_DIR}, 				1, {0},	10,		"alive",	0, 0},
	{"ld",		2, (t_arg_type[]){T_DIR | T_IND, T_REG},2, {0},	5,		"load",		1, 0},
	{"st",		2, (t_arg_type[]){T_REG, T_IND | T_REG},3, {0},	5,		"store",	1, 0},
	{"add",		3, (t_arg_type[]){T_REG, T_REG, T_REG}, 4, {0},	10,		"add",		1, 0},
	{"sub",		3, (t_arg_type[]){T_REG, T_REG, T_REG}, 5, {0},	10,		"sub", 		1, 0},
	{"and",		3, (t_arg_type[]){T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, {0},	6,		"and",		1, 0},
	{"or",		3, (t_arg_type[]){T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	7, {0},	6,		"or",		1, 0},
	{"xor",		3, (t_arg_type[]){T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	8, {0},	6,		"xor",		1, 0},
	{"zjmp",	1, (t_arg_type[]){T_DIR},				9, {0},	20,		"jump", 	0, 1},
	{"ldi", 	3, (t_arg_type[]){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},	10, {0},	25,		"load i",	1, 1},
	{"sti", 	3, (t_arg_type[]){T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},11, {0},	25,		"store i",	1, 1},
	{"fork", 	1, (t_arg_type[]){T_DIR},				12, {0},	800,	"fork",		0, 1},
	{"lld", 	2, (t_arg_type[]){T_DIR | T_IND, T_REG},		13, {0},	10, 	"l load",	1, 0},
	{"lldi", 	3, (t_arg_type[]){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},	14, {0},	50,		"ll index", 1, 1},
	{"lfork", 	1, (t_arg_type[]){T_DIR},				15, {0},	1000,	"long fork",0, 1},
	{"aff", 	1, (t_arg_type[]){T_REG},				16, {0},	2,		"aff",		1, 0},
};

static inline void		ft_add_unit_to_lst(t_list **unit_lst
										, t_semantic_unit *unit)
{
	t_list	*tmp;

	if (!(tmp = (t_list*)ft_memalloc(sizeof(t_list))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	tmp->content = unit;
	ft_lstadd(unit_lst, tmp);
}

t_bin_buffer			*ft_parse(int fd)
{
	t_bin_buffer	*bin;
	t_semantic_unit	*unit;
	t_list			*unit_lst;
	int32_t			current_case;
	char			*line;

	current_case = -1;
	bin = ft_create_bin_buffer(CHAMP_MAX_SIZE);
	unit_lst = NULL;
	while ((get_next_line(fd, &line)) > 0)
	{
		ft_discard_comments(line);
		(*ft_get_instruction_count())++;
		unit = ft_tokenize(line, bin);
		if (-1 == ft_parse_semantic_unit(unit, bin))
			ft_error_exit(4, (char*[]){PARSING_ERROR, ft_static_ulltoa(unit->line_nbr), ": ", line}, EXIT_FAILURE);
		ft_add_unit_to_lst(&unit_lst, unit);
	}
	ft_seek_labels(unit_lst, bin);
	return (bin);
}
