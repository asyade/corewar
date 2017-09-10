#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>

void		usage(void)
{
	ft_putendl("Usage    : ./corw [-d N -s N | -v [0-31] | -nc] [--bonus] [-n] <champ.cor>");
	ft_putendl("#### TEXT OUTPUT MODE");
	ft_putendl("    -d N : Dumps memory after N cycles then exits");
	ft_putendl("    -s N : Runs N cycles, dumps memory, read char, then repeats");
	ft_putendl("    -v N : Verbosity levels, can be added together to enable several");
	ft_putendl("            - 0 : Show only essentials");
	ft_putendl("            - 1 : Show lives");
	ft_putendl("            - 2 : Show cycles");
	ft_putendl("            - 4 : Show operations (Params are NOT litteral ...)");
	ft_putendl("            - 8 : Show deaths");
	ft_putendl("            - 16 : Show PC movements (Except for jumps)");
	ft_putendl("#### NCURSES OUTPUT MODE");
	ft_putendl("    -nc  : Ncurses output mode");
	ft_putendl("#### NOISE BONUS");
	ft_putendl("    --bonus");
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
	p->verbose = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-v"))
		{
			p->flag = P_VERBOSE | (p->flag & ~P_NCURSE);
			if (i + 1 >= ac)
				usage();
			p->verbose = atoi(av[++i]);
		}
		else if (ft_strequ(av[i], "-nc"))
			p->flag = P_NCURSE | (p->flag & ~P_VERBOSE);
		else if (ft_strequ(av[i], "--bonus"))
			p->flag |= P_SOUND;
		else if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-s"))
		{
			if (ac - i <= 1)
				usage();
			p->flag |= ft_strequ(av[i], "-s") ? P_DUMP | P_DUMPREP : P_DUMP;
			p->dump = ft_atoi(av[++i]);
			p->basedump = p->dump;
		}
		else if (!read_param_champ(p, av, ac, &i))
			usage();
	}
	if (p->count == 0 || ac == 0)
		usage();
	check_params(p);
	return (p);
}
