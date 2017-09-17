/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/09/17 22:53:28 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdint.h>

/*
** Arg_types
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define T_REG_CODE_SIZE 1
# define T_IND_CODE_SIZE 2
# define T_DIR_CODE_SIZE 4

/*
** Parameter encoding
*/

typedef struct	s_encoding_byte
{
	t_arg_type			arg_type;
	uint8_t				code;
}				t_encoding_byte;

# define REG_CODE			1 //0b01
# define DIR_CODE			2 //0b10
# define IND_CODE			3 //0b11

/*
** Opcodes
*/

typedef struct	s_op
{
	char		*name;
	uint64_t	nbr_arg;
	t_arg_type	*arg_type;
	uint8_t		opcode;
	char		pad[7];
	uint64_t	nbr_cycles;
	char		*describ;
	uint32_t	octal_code;
	uint32_t	label_size;
}				t_op;

# define OP_NBR 17
extern t_op    op_tab[OP_NBR];

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE

#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4 * 1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			pad[3];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			pad2[3];
}					header_t;

#endif
