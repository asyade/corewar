/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/09/14 00:12:02 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] = 
{
	//name	pcount	params					ID	Cycles	describ		PC IND_2/4
	{"live",	1, {T_DIR}, 				1,	10,		"alive",	0, 0},
	{"ld",		2, {T_DIR | T_IND, T_REG}, 	2,	5,		"load",		1, 0},
	{"st",		2, {T_REG, T_IND | T_REG}, 	3,	5,		"store",	1, 0},
	{"add",		3, {T_REG, T_REG, T_REG}, 	4,	10,		"add",		1, 0},
	{"sub",		3, {T_REG, T_REG, T_REG}, 	5,	10,		"sub", 		1, 0},
	{"and",		3, {T_RID, T_RID, T_REG}, 	6,	6,		"and",		1, 0},
	{"or",		3, {T_RID, T_RID, T_REG},	7,	6,		"or",		1, 0},
	{"xor",		3, {T_RID, T_RID, T_REG},	8,	6,		"xor",		1, 0},
	{"zjmp",	1, {T_DIR},					9,	20,		"jump", 	0, 1},
	{"ldi", 	3, {T_RID, T_DR, T_REG},	10,	25,		"load i",	1, 1},
	{"sti", 	3, {T_RID, T_DIR | T_REG},	11,	25,		"store i",	1, 1},
	{"fork", 	1, {T_DIR},					12,	800,	"fork",		0, 1},
	{"lld", 	2, {T_DIR | T_IR},			13,	10, 	"l load",	1, 0},
	{"lldi", 	3, {T_RID, T_DR, T_REG},	14,	50,		"ll index", 1, 1},
	{"lfork", 	1, {T_DIR},					15,	1000,	"long fork",0, 1},
	{"aff", 	1, {T_REG},					16,	2,		"aff",		1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
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

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;