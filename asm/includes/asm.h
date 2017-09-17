/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:06:39 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/17 21:34:00 by sclolus          ###   ########.fr       */
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
# define BIN_FILE_EXTENSION ".cor"

/*
** Parsing
*/

# define CHARSET_WHITESPACES " \n\t\r\b"
# define MAX_NBR_PARAMS 3

typedef struct	s_label
{
	char		*name;
	uint64_t	instruction_index;
	uint64_t	relative_address;
}				t_label;

typedef struct	s_bin_buffer
{
	char		*buffer;
	uint64_t	capacity;
	uint64_t	offset;
	header_t	header;
	uint16_t	name_flag;
	uint16_t	comment_flag;
	char		pad[4];
}				t_bin_buffer;

void			ft_check_file_extansion(char *filename);
t_bin_buffer	*ft_parse(int fd);
t_arg_type		ft_get_instruction_param_type(char *param);
uint32_t		ft_get_instruction_params(char *line, char **params);

uint64_t		*ft_get_instruction_count(void);
t_list			**ft_get_label_lst(void);
void			ft_discard_comments(char *line);

/*
** Tokenization
*/

# define CHARSET_SEPARATORS " \t,"
# define CHARSET_DECIMAL "-0123456789"

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

typedef union	u_param_content
{
/* 	uint8_t	reg_value[T_REG_CODE_SIZE]; */
/* 	int8_t	indirect_value[T_IND_CODE_SIZE]; */
/* 	int8_t	direct_value[T_DIR_CODE_SIZE]; */
	uint8_t	reg_value;
	int32_t	direct_value;
	int16_t	indirect_value;
	uint8_t	raw_value[sizeof(uint64_t)];
}				t_param_content;

typedef struct	s_param
{
	t_param_content	content;
	t_arg_type		param_type;
	char			pad[1];
	uint16_t		size;
	uint32_t		label_to_seek;
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
	uint64_t		relative_address;
	t_token_content	token_content;
	t_token_type	token_type;
	char			pad[4];
}				t_token;

typedef struct	s_semantic_unit
{
	char		*line;
	uint64_t	line_nbr;
	uint64_t	relative_address;
	t_token		tokens[MAX_NBR_TOKEN];
	uint64_t	tokens_nbr;
}				t_semantic_unit;


char					**ft_split(char *str, char *separators);
t_semantic_unit			*ft_tokenize(char *line, t_bin_buffer *bin);

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
** **Interpretation**
*/

typedef int32_t (*t_f_interpret_token)(t_semantic_unit *, uint64_t, t_token *, t_bin_buffer *);

int32_t	ft_interpret_param(t_semantic_unit *unit, uint64_t token_index, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_content(t_semantic_unit *unit, uint64_t token_index, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_comment(t_semantic_unit *unit, uint64_t token_index, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_name(t_semantic_unit *unit, uint64_t token_index, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_instruction(t_semantic_unit *unit, uint64_t token_index, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_err(t_semantic_unit *unit, uint64_t token_index, t_token *token, t_bin_buffer *bin);

t_list	*ft_find_label(char *name, t_list *label_lst);
int32_t	ft_interpret_label(t_semantic_unit *unit, uint64_t token_index, t_token *token, t_bin_buffer *bin);

/*
** Parsing actions
*/

typedef int32_t	(*t_parsing_action)(char *buffer);

int32_t		ft_parse_semantic_unit(t_semantic_unit *unit, t_bin_buffer *bin);
void		ft_fill_bin_with_instruction(t_semantic_unit *unit, uint64_t index
									 , t_bin_buffer *bin);
uint8_t		ft_make_encoding_byte(t_arg_type *args, uint64_t nbr_args);
int32_t		ft_check_params_integrity(t_semantic_unit *unit, uint64_t index);

int32_t		ft_fill_header_name(t_semantic_unit *unit, t_bin_buffer *bin);
int32_t		ft_fill_header_comment(t_semantic_unit *unit, t_bin_buffer *bin);

typedef struct	s_f_param_value
{
	int32_t		(*f)(t_token *, uint8_t);
	t_arg_type	id;
	char		pad[7];
}				t_f_param_value;

int32_t		ft_get_params_value(t_semantic_unit *unit
								, uint64_t index);
void		ft_seek_labels(t_list *unit_lst, t_bin_buffer *bin);
int32_t		ft_is_token_decimal(char *token);

/*
** Bin buffer
*/

t_bin_buffer	*ft_create_bin_buffer(uint64_t capacity);

/*
** Bin creation
*/

void	ft_create_corewar_file(char *filename, t_bin_buffer *bin);
char	*ft_get_bin_filename(char *filename);

/*
** Endianness Swap
*/

uint16_t	ft_bswap_u16(uint16_t to_swap);
uint32_t	ft_bswap_u32(uint32_t to_swap);

/*
** Error handling
*/

# define ASM_PARAM_ERROR "Invalid parameter provided to asm: "
# define ASM_USAGE "./asm [file.s]"
# define INVALID_FILE_EXTENSION "Invalid file extension: "
# define PARSING_ERROR "Parsing error near: "
# define INVALID_PARAMS_NBR "Invalid number of parameters provided to instruction: "
# define INVALID_PARAM_TYPE "Invalid parameter type: "
# define INVALID_INSTRUCTION "Invalid instruction: "
# define AT_LINE " at line: "
# define ILLEGAL_USE_INSTRUCTION "Illegal use of instruction: "
# define ILLEGAL_PARAM_INVOCATION "Illegal invocation of parameter: "
# define LABEL_REDEFINITION "Label redefinition: "
# define EXPECTED_EXPRESSION "Expected expression after: "
# define INVALID_EXPRESSION "Invalid expression: "
# define NAME_COMMENT_REDEFINITION "Redefinition of token: "
# define NAME_TOO_LONG ".name value is too long"
# define COMMENT_TOO_LONG ".comment value is too long"
# define INVALID_REG_NUMBER "Invalid register number: "
# define UNKOWN_LABEL_INVOCATION "Invocation of unkown label: "
# define CREATE_FILE_ERROR "Failed to create binary file"

NORETURN	ft_put_asm_usage(char *str);

#endif
