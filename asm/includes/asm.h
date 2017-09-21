/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 00:06:39 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/21 22:32:01 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define NORETURN __attribute__((noreturn)) void
# include <stdio.h>
# include "libft.h"
# include <stdint.h>
# include <unistd.h>
# include "op.h"
# include <fcntl.h>
# include "colors.h"

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
	t_header	header;
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

# define MAX_PARAMS_NBR MAX_NBR_PARAMS
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
}				t_token_content;

typedef struct	s_token
{
	char			*token;
	uint64_t		len;
	uint64_t		column;
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

typedef int32_t	(*t_f_lexing)(char *);

void					ft_assign_tokens_type(t_semantic_unit *unit);
void					ft_assign_token_type(t_semantic_unit *unit
											, uint64_t token_index);
/*
** **Interpretation**
*/

typedef int32_t	(*t_f_interpret_token)(t_semantic_unit *, uint64_t
									, t_token *, t_bin_buffer *);
int32_t	ft_interpret_tokens(t_semantic_unit *unit
						, t_bin_buffer *bin);
int32_t	ft_interpret_param(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_content(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_comment(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_name(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_instruction(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin);
int32_t	ft_interpret_err(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin);

t_list	*ft_find_label(char *name, t_list *label_lst);
int32_t	ft_interpret_label(t_semantic_unit *unit, uint64_t token_index
						, t_token *token, t_bin_buffer *bin);

int32_t	ft_check_label_integrity(char *label);
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
void		ft_check_bin_integrity(t_bin_buffer *bin);

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
t_bin_buffer	*ft_realloc_bin_buffer(t_bin_buffer *bin);

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
** Diagnostics
*/

typedef enum	e_diagnostic_kind
{
	DK_UNKNOWN = 0,
	DK_ERROR,
	DK_WARNING,
	DK_INTERNAL_ERROR,
	DK_LAST_KIND,
}				t_dk_kind;

typedef struct	s_diagnostic_location
{
	uint64_t	line;
	uint64_t	column;
	uint64_t	len;
}				t_dk_location;

typedef struct	s_diagnostic_color
{
	char		*font;
	char		*back;
	char		*style;
}				t_dk_color;

typedef struct	s_diagnostic_info
{
	t_dk_location	location;
	t_dk_color		colors;
	char			*content;
	char			*line;
	char			*msg;
	t_dk_kind		kind;
	uint8_t			abort_on_dk;
	uint8_t			force_no_abort;
	uint8_t			context;
	char			pad[1];
}				t_dk_info;

typedef struct	s_diagnostic_conf
{
	char		*msg;
	t_dk_kind	kind;
	uint8_t		context;
}				t_dk_conf;

extern t_dk_info	g_dk_info;

int32_t			ft_diagnostic(t_dk_info *dk_info, char *msg
							, int32_t return_value);
void			ft_put_diagnostic(t_dk_info *dk_info);

t_dk_color		ft_get_dk_colors_to_kind(t_dk_kind kind);
void			ft_put_dk_colors(t_dk_color colors);
void			ft_dk_colors_reset(void);
t_dk_location	ft_set_dk_location(t_dk_info *dk_info, uint64_t line
								, uint64_t column, uint64_t token_nbr);
uint8_t			*ft_get_abort_on_dk(void);
t_dk_kind		ft_get_kind_from_msg(const char *msg);
void			ft_init_dk_info(t_dk_info *dk_info);
t_dk_conf		ft_get_dk_conf_from_msg(const char *msg);

/*
** Error handling
*/

# define ASM_PARAM_ERROR "Invalid parameter provided to asm: "
# define ASM_USAGE "./asm [file.s]"
# define INVALID_FILE_EXTENSION "Invalid file extension: "
# define PARSING_ERROR "Parsing error at line "
# define PROVIDED " provided to instruction: "
# define INVALID_PARAMS_NBR "Invalid number of parameters"PROVIDED
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
# define NAME_TOO_SHORT ".name value is too short"
# define COMMENT_TOO_LONG ".comment value is too long"
# define INVALID_REG_NUMBER "Invalid register number: "
# define UNKNOWN_LABEL_INVOCATION "Invocation of unkown label: "
# define INVALID_LABEL_CHARS "Illegal character in label name: "
# define CREATE_FILE_ERROR "Failed to create binary file"
# define UNAMED_BIN_FILE "Unamed binary file"
# define WARNING "Warning: "
# define NO_COMMENT_DEFINED "No comment has been defined"
# define EMPTY_TEXT "Empty text"

NORETURN	ft_put_asm_usage(char *str);

#endif
