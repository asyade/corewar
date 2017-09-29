/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 01:39:14 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>

t_param		*params(void)
{
	static t_param	params = {0, 0, 0, 0, 0, -1, MACRO_DUTURUF};

	return (&params);
}

int			read_param_champ(t_param *p, char **av, int ac, int *i)
{
	if (p->count >= 4 || (ft_strequ("-n", av[*i]) && ac - *i <= 2))
		return (0);
	if (ft_strequ("-n", av[*i]))
	{
		p->champs[p->count].number = atoi(av[++*i]);
		*i += 1;
	}
	else
		p->champs[p->count].number = p->count + 1;
	p->champs[p->count++].path = av[*i];
	return (1);
}

void		check_params(t_param *p)
{
	int			i;
	struct stat	st;
	char		*ext;

	i = -1;
	while (++i < p->count)
	{
		if (stat(p->champs[i].path, &st) != 0 || !(st.st_mode & S_IFREG))
			ft_printf("error: %s: file not found !\n", p->champs[i].path);
		if (!(ext = ft_strrchr(p->champs[i].path, '.')) ||
				!ft_strequ(ext, ".cor"))
			ft_printf("error: %s: invalide file !\n", p->champs[i].path);
	}
}

int			get_param(int ac, char **av, int *i, t_param *p)
{
	if (ft_strequ(av[*i], "-v"))
	{
		p->flag = P_VERBOSE | (p->flag & ~P_NCURSE);
		(*i + 1 >= ac) ? usage() : NULL;
		p->verbose = atoi(av[++(*i)]);
	}
	else if (ft_strequ(av[*i], "-vd"))
	{
		p->flag = p->flag & ~P_NCURSE;
		(*i + 2 >= ac) ? usage() : NULL;
		p->verbdellay = atoi(av[++(*i)]);
		p->verbose = atoi(av[++(*i)]);
	}
	else if (ft_strequ(av[*i], "-a"))
		p->flag |= P_SHOWAFF;
	else if (ft_strequ(av[*i], "-d") || ft_strequ(av[*i], "-s"))
	{
		(ac - *i <= 1) ? usage() : NULL;
		p->flag |= ft_strequ(av[*i], "-s") ? P_DUMP | P_DUMPREP : P_DUMP;
		p->dump = ft_atoi(av[++*i]);
		p->basedump = p->dump;
	}
	else
		return (0);
	return (1);
}

t_param		*read_params(int ac, char **av)
{
	int		i;
	t_param	*p;

	i = -1;
	p = params();
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-nc"))
			p->flag = P_NCURSE | (p->flag & ~P_VERBOSE);
		else if (ft_strequ(av[i], "--bonus"))
			p->flag |= P_SOUND;
		else if (!get_param(ac, av, &i, p) && !read_param_champ(p, av, ac, &i))
			usage();
	}
	(p->count == 0 || ac == 0) ? usage() : check_params(p);
	return (p);
}
