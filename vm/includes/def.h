/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:54:30 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

typedef int				t_vsize;
typedef long int		t_vptr;
typedef int				t_reg;
typedef char			t_char;
typedef char			t_sbyte;
typedef unsigned char	t_byte;
typedef short			t_int16;
typedef int				t_int32;
typedef long			t_int64;
typedef uint16_t		t_uint16;
typedef uint32_t		t_uint32;
typedef uint64_t		t_uint64;
typedef uint32_t		t_flags;

# define TRUE			1
# define FALS			0

# define T_REG			1
# define T_DIR			2
# define T_IND			3

# define FT_REG			1
# define FT_DIR			2
# define FT_IND			4

# define MAX_PLAYERS	4
# define MEM_SIZE		(MAX_PLAYERS * 1024)
# define IDX_MOD		(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE	(MEM_SIZE / 6)

# define REG_NUMBER		16
# define PROG_NAME_LEN  128
# define COMMENT_LEN	2048
# define COREWAR_MAGIC	0xea83f3

# define CYCLE_TO_DIE	1536
# define CYCLE_DELTA	50
# define NBR_LIVE		21
# define MAX_CHECKS		10

# define BASE_HEX		"0123456789ABCDEF"
# define OP_NBR 17

#endif
