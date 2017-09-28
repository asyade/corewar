/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:13:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 22:02:38 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

/*
** Charsets
*/

# define VALID_CHARS "dxshl"
# define CONVERSION_FLAGS "dxs"

# define HEXA_MIN_CHARSET "0123456789abcdef"
# define HEXA_MAX_CHARSET "0123456789ABCDEF"

int				ft_printf(const char *format, ...);

typedef enum	e_length_modifier
{
	NORMAL = 0,
	L,
	LL,
	H,
	HH,
	SUPPORTED_LENGTH_MODIFIERS,
}				t_length_modifier;

typedef struct	s_arg
{
	char				conversion;
	char				pad[3];
	t_length_modifier	len_mod;
}				t_arg;

typedef struct	s_conv
{
	char			conversion;
	int32_t			(*f)(void *, t_arg*);
}				t_conv;

/*
** Parsing
*/

t_arg			*ft_get_arg(const char *str, va_list *v_arg, t_arg *arg);
void			ft_get_conversion(const char *str, t_arg *arg);
int64_t			ft_cast(void *ptr, t_arg *arg);

/*
** Conversions
*/

int32_t			ft_convertor(void *nbr, t_arg *arg);
int32_t			ft_convertor_hexa(void *nbr, t_arg *arg);
int32_t			ft_convertor_str(void *str, t_arg *arg);
int32_t			ft_convertor_decimal(void *nbr, t_arg *arg);

/*
** Sprintf conversions
*/

int				ft_sprintf(char *str, const char *format, ...);

typedef struct	s_sprintf_conv
{
	char			conversion;
	int32_t			(*f)(void *, t_arg*, char*);
}				t_sprintf_conv;

int32_t			ft_sconvertor(void *nbr, t_arg *arg, char *buf);
int32_t			ft_sconvertor_hexa(void *nbr, t_arg *arg, char *buf);
int32_t			ft_sconvertor_str(void *str, t_arg *arg, char *buf);
int32_t			ft_sconvertor_decimal(void *nbr, t_arg *arg, char *buf);

#endif
