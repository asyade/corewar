/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 02:08:01 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/12 07:18:34 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op    op_tab[OP_NBR] =
{
	//name		?	params					ID	Cycles	describ		PC IND_2/4
	{"live",	1, (t_arg_type[]){T_DIR}, 				1,	10,		"alive",	0, 0},
	{"ld",		2, (t_arg_type[]){T_DIR | T_IND, T_REG}, 	2,	5,		"load",		1, 0},
	{"st",		2, (t_arg_type[]){T_REG, T_IND | T_REG}, 	3,	5,		"store",	1, 0},
	{"add",		3, (t_arg_type[]){T_REG, T_REG, T_REG}, 	4,	10,		"add",		1, 0},
	{"sub",		3, (t_arg_type[]){T_REG, T_REG, T_REG}, 	5,	10,		"sub", 		1, 0},
	{"and",		3, (t_arg_type[]){T_DIR, T_DIR, T_REG}, 	6,	6,		"and",		1, 0},
	{"or",		3, (t_arg_type[]){T_DIR, T_DIR, T_REG},	7,	6,		"or",		1, 0},
	{"xor",		3, (t_arg_type[]){T_DIR, T_DIR, T_REG},	8,	6,		"xor",		1, 0},
	{"zjmp",	1, (t_arg_type[]){T_DIR},					9,	20,		"jump", 	0, 1},
	{"ldi", 	3, (t_arg_type[]){T_DIR, T_DIR, T_REG},	10,	25,		"load i",	1, 1},
	{"sti", 	3, (t_arg_type[]){T_DIR, T_DIR | T_REG},	11,	25,		"store i",	1, 1},
	{"fork", 	1, (t_arg_type[]){T_DIR},					12,	800,	"fork",		0, 1},
	{"lld", 	2, (t_arg_type[]){T_DIR | T_DIR},			13,	10, 	"l load",	1, 0},
	{"lldi", 	3, (t_arg_type[]){T_DIR, T_DIR, T_REG},	14,	50,		"ll index", 1, 1},
	{"lfork", 	1, (t_arg_type[]){T_DIR},					15,	1000,	"long fork",0, 1},
	{"aff", 	1, (t_arg_type[]){T_REG},					16,	2,		"aff",		1, 0},
};

static inline size_t	ft_get_instruction_len(const char *line)
{
	size_t		i;

	i = 0;
	while (line[i])
	{
		if ((ft_strchr(CHARSET_WHITESPACES, line[i])))
			return (i);
		i++;
	}
	return (i);
}

static inline int32_t	ft_get_special_case(char *line)
{
	char		*cases[] = {".name", ".comment"};
	uint32_t	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(*cases))
	{
		if (ft_strnequ(line, cases[i], sizeof(cases[i])))
			return (OP_NBR + (int32_t)i);
		i++;
	}
	return (-1);
}

static inline size_t	ft_parse_label(char *line)
{
	size_t	i;
	t_list	**label_lst;
	t_list	*tmp;
	char	*label_name;

	i = 0;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (line[i] == LABEL_CHAR)
	{
		label_lst = ft_get_label_lst();
		if (!(label_name = ft_strndup(line, i++))
			|| !(tmp = ft_lstnew(&(t_label){label_name
			, *ft_get_instruction_count()}, sizeof(t_label))))
			ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
		ft_lstadd(label_lst, tmp);
		while (ft_strchr(CHARSET_WHITESPACES, line[i]))
			i++;
		return (i);
	}
	return (0);
}

static inline int32_t	ft_get_case(char *line)
{
	size_t	instruction_len;
	int32_t	i;

	i = 0;
	line += ft_parse_label(line);
	if (*line == '.')
		return (ft_get_special_case(line));
	instruction_len = ft_get_instruction_len(line);
	while (i < OP_NBR)
	{
		if (ft_strnequ(line, op_tab[i].name, instruction_len))
		{
			if (ft_check_params_integrity(i, line + instruction_len))
				return (i);
			return (-1);
		}
		i++;
	}
	return (-1);
}

char					*ft_parse(int fd)
{
//	header_t	header;
	int32_t		current_case;
	char		*buffer;
	char		*line;
	char		*tmp;

	current_case = -1;
	if (!(buffer = (char*)ft_memalloc(sizeof(char) * (CHAMP_MAX_SIZE + 1))))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	while ((get_next_line(fd, &line)) > 0)
	{
		ft_discard_comments(line);
		tmp = line;
		if (!(line = ft_strtrim(line)))
			ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
		free(tmp);
		if (-1 == (current_case = ft_get_case(line))
			/* || -1 == parsing_actions[current_case](buffer) */)
			ft_error_exit(1, (char*[]){PARSING_ERROR, line}, EXIT_FAILURE);
		(*ft_get_instruction_count())++;
	}
	return (buffer);
}
