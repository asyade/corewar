/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:06:39 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/12 07:14:46 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define NORETURN __attribute__((noreturn)) void
# include "libft.h"
# include <stdint.h>
# include <stdio.h>//
# include <unistd.h>
# include "op.h"
# include <fcntl.h>

# define BIN_NAME "asm: "
# define ASM_FILE_EXTENSION ".s"

/*
** Parsing
*/

# define CHARSET_WHITESPACES " \n\t\r\b"
# define MAX_NBR_PARAMS 3

typedef struct	s_label
{
	char		*name;
	uint64_t	instruction_index;
}				t_label;

void		ft_check_file_extansion(char *filename);
char		*ft_parse(int fd);
t_arg_type	ft_get_instruction_param_type(char *param);
uint32_t	ft_get_instruction_params(char *line, char **params);
int32_t		ft_check_params_integrity(int32_t instruction_index
										, char *line);


uint64_t	*ft_get_instruction_count(void);
t_list		**ft_get_label_lst(void);
void		ft_discard_comments(char *line);

/*
** Error handling
*/

# define ASM_PARAM_ERROR "Invalid parameter provided to asm: "
# define ASM_USAGE "./asm [file.s]"
# define INVALID_FILE_EXTENSION "Invalid file extension: "
# define PARSING_ERROR "Parsing error near: "
# define INVALID_PARAMS_NBR "Invalid number of parameters provided to instruction: "
# define INVALID_PARAM_TYPE "Invalid parameter type, parameter number: "

NORETURN	ft_put_asm_usage(char *str);

#endif
