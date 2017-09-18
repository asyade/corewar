/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diagnostic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 23:01:34 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/19 01:53:19 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	ft_put_dk_colors(t_dk_color colors)
{
	ft_putstr_fd(colors.font, 2);
	ft_putstr_fd(colors.back, 2);
	ft_putstr_fd(colors.style, 2);
}

static inline void	ft_dk_colors_reset(void)
{
	ft_putstr_fd(RESET, 2);
//	ft_putstr_fd(BACK_RESET, 2);
//	ft_putstr_fd(RESET_FONT, 2);
}

static inline void	ft_put_dk_kind(t_dk_info *dk_info)
{
	static const char	*kind_strings[] = {
		"Unkown diagnostic: ",
		"Error: ",
		"Warning: ",
		"Internal error: ",
		"Unexpected diagnostic: "};

	ft_put_dk_colors(dk_info->colors);
	ft_putstr_fd(kind_strings[dk_info->kind], 2);
	ft_dk_colors_reset();
}

static inline void	ft_put_dk_location(t_dk_location location)
{
	if (location.line == 0)
		return ;
	ft_putstr_fd(ft_static_ulltoa(location.line), 2);
	ft_putchar_fd(':', 2);
	ft_putstr_fd(ft_static_ulltoa(location.line), 2);
	ft_putstr_fd(": ", 2);
}

static inline void	ft_put_dk_context(t_dk_info *dk_info)
{
	uint64_t	len;

	if (!dk_info->location.line || !dk_info->context)
		return ;
	len = ft_strlen(dk_info->line) - (dk_info->location.column + dk_info->location.len);
	write(2, dk_info->line, dk_info->location.column);
	ft_putstr_fd(ITALICS, 2);
	ft_putstr_fd(UNDERLINE, 2);
	ft_putstr_fd(dk_info->colors.font, 2);
	write(2, dk_info->line + dk_info->location.column, dk_info->location.len);
	ft_dk_colors_reset();
	write(2, dk_info->line + dk_info->location.column + dk_info->location.len, len);
}

void				ft_put_diagnostic(t_dk_info *dk_info)
{
	ft_putstr_fd(BIN_NAME, 2);
	if (dk_info->context)
		ft_put_dk_location(dk_info->location);
	ft_put_dk_kind(dk_info);
	ft_putstr_fd(dk_info->msg, 2);
	if (dk_info->content)
	{
		ft_putstr_fd((char*)dk_info->content, 2);
		ft_putchar_fd('\n', 2);
		if (dk_info->line && dk_info->context)
		{
			ft_put_dk_context(dk_info);
			ft_putchar_fd('\n', 2);
		}
	}
}

int32_t				ft_diagnostic(t_dk_info *dk_info, char *msg, int32_t return_value)
{
	t_dk_conf	conf;

	dk_info->msg = msg;
	conf = ft_get_dk_conf_from_msg(msg);
	if (dk_info->kind == DK_UNKNOWN)
	{
		dk_info->kind = conf.kind;
		dk_info->context = conf.context;
	}
	dk_info->colors = ft_get_dk_colors_to_kind(dk_info->kind);
	dk_info->abort_on_dk = *ft_get_abort_on_dk();
	ft_put_diagnostic(dk_info);
	if (dk_info->kind != DK_WARNING || dk_info->abort_on_dk)
		exit(EXIT_FAILURE);
	return (return_value);
}
