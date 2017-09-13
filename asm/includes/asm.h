/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:06:39 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/13 09:53:33 by sclolus          ###   ########.fr       */
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
** Tokenization
*/

# define CHARSET_SEPARATORS " \t,"

# define MAX_PARAMS_NBR MAX_NBR_PARAMS //
# define MAX_LABEL_NBR 1
# define MAX_NBR_TOKEN MAX_LABEL_NBR + 1 + MAX_PARAMS_NBR

typedef enum	e_token_type
{
	ERR = 0,
	INSTRUCTION,
	NAME,
	COMMENT,
	CONTENT,
	PARAM,
	LABEL,
}				t_token_type;

typedef struct	u_param_content
{
	uint8_t	reg_value[T_REG_CODE_SIZE];
	uint8_t	indirect_value[T_IND_CODE_SIZE];
	uint8_t	direct_value[T_DIR_CODE_SIZE];
	uint8_t	raw_value[sizeof(uint64_t)];
}				t_param_content;

typedef struct	s_param
{
	t_param_content	content;
	t_arg_type		param_type;
}				t_param;

typedef union	u_token_content
{
	t_param	param;
	uint8_t	opcode;
	char	*label;
	char	*content;
}				t_token_content;

typedef struct	s_token
{
	char			*token;
	t_token_content	token_content;
	t_token_type	token_type;
	char			pad[4];
}				t_token;

typedef struct	s_semantic_unit
{
	char		*line;
	uint64_t	line_nbr;
	t_token		tokens[MAX_NBR_TOKEN];
	uint64_t	tokens_nbr;
}				t_semantic_unit;

char					**ft_split(char *str, char *separators);
t_semantic_unit			*ft_tokenize(char *line);

/*
** **Lexing**
*/

int32_t					ft_lex_is_label(char *token);
int32_t					ft_lex_is_instruction(char *token);
int32_t					ft_lex_is_param(char *token);
int32_t					ft_lex_is_content(char *token);
int32_t					ft_lex_is_comment(char *token);
int32_t					ft_lex_is_name(char *token);

/*
** Parsing actions
*/

typedef int32_t	(*t_parsing_action)(char *buffer);

char		ft_make_encoding_byte(t_arg_type *args, uint32_t nbr_args);

/*
** Error handling
*/

# define ASM_PARAM_ERROR "Invalid parameter provided to asm: "
# define ASM_USAGE "./asm [file.s]"
# define INVALID_FILE_EXTENSION "Invalid file extension: "
# define PARSING_ERROR "Parsing error near: "
# define INVALID_PARAMS_NBR "Invalid number of parameters provided to instruction: "
# define INVALID_PARAM_TYPE "Invalid parameter type, parameter number: "
# define INVALID_INSTRUCTION "Invalid instruction: "
# define AT_LINE " at line: "
# define ILLEGAL_USE_INSTRUCTION "Illegal use of instruction: "

NORETURN	ft_put_asm_usage(char *str);

#endif
