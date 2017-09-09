#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>

void		usage(void)
{
	ft_putendl("./corewar [-dump cycle] [prog_name]...");
	exit(1);
}

t_param		*params(void)
{
	static  t_param     params;
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
			pcri("%s: file not found !\n", p->champs[i].path);
		if (!(ext = ft_strrchr(p->champs[i].path, '.')) || !ft_strequ(ext, ".cor"))
			pcri("%s: invalide file !\n", p->champs[i].path);
	}
}

t_param		*read_params(int ac, char **av)
{
	int		i;
	t_param	*p;

	i = -1;
	p = params();
	p->count = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-v"))
			p->flag = P_VERBOSE | (p->flag & ~P_NCURSE);
		else if (ft_strequ(av[i], "-nc"))
			p->flag = P_NCURSE | (p->flag & ~P_VERBOSE);
		else if (ft_strequ(av[i], "-sound"))
			p->flag |= P_SOUND;
		else if (ft_strequ(av[i], "-dump") || ft_strequ(av[i], "-dumpCol"))
		{
			if (ac - i <= 1)
				usage();
			p->flag |= ft_strequ(av[i], "-dumpCol") ? P_DUMP | P_DUMPCOL : P_DUMP;
			p->dump = ft_atoi(av[++i]);
		}
		else if (!read_param_champ(p, av, ac, &i))
			usage();
	}
	if (p->count == 0 || ac == 0)
		usage();
	check_params(p);
	return (p);
}
