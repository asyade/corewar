/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:44:18 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		usage(void)
{
	ft_putendl("Usage ./corw [-d N -s N -v N -nc] [-n] <champ.cor>");
	ft_putendl("#### TEXT OUTPUT MODE");
	ft_putendl("-a      : Prints output from \"aff\"");
	ft_putendl("-d N    : Dumps memory after N cycles then exits");
	ft_putendl("-s N    : Runs N cycles, dumps memory, then repeats");
	ft_putendl("-v N    : Verbosity levels, can be added together");
	ft_putendl("-vd D N : the same as -v, displays nothing before cycle D");
	ft_putendl("        - 0  : Show only essentials");
	ft_putendl("        - 1  : Show lives");
	ft_putendl("        - 2  : Show cycles");
	ft_putendl("        - 4  : Show operations (Params are NOT litteral ...)");
	ft_putendl("        - 8  : Show deaths");
	ft_putendl("        - 16 : Show PC movements (Except for jumps)");
	ft_putendl("        - 32 : List all instructions used");
	ft_putendl("#### NCURSES OUTPUT MODE");
	ft_putendl("    -nc  : Ncurses output mode");
	ft_putendl("#### NOISE BONUS");
	ft_putendl("    --bonus");
	exit(1);
}