#include "corewar.h"
#include <fcntl.h>
#include <sys/types.h>

static int		checkSize(char *nm, int fd, int size)
{
	off_t		real;

	real = lseek(fd, 0, SEEK_END) - sizeof(t_champHeader);
	if (real != size)
	{
		pcri("%s: file size different from header size\n", nm);
		return (0);
	}
	lseek(fd, -real, SEEK_CUR);
	return (1);
}

static int		readChampDef(char *src, int i, t_champ *ch)
{
	t_int32		fd;

	if (!(fd = open(src, O_RDONLY)))
		return (0);
	if (read(fd, &ch->header, sizeof(t_champHeader)) < 0)
	{
		pcri("%s: file not found\n", src);
	}
	ch->header.magic = BSWAP32(ch->header.magic);
	ch->header.size = BSWAP32(ch->header.size);
	ch->header.name[PROG_NAME_LEN] = '\0';
	ch->header.comment[PROG_NAME_LEN] = '\0';
	ch->number = i;
	if (!checkSize(src, fd, ch->header.size))
		return (0);
	if (ch->header.magic != COREWAR_MAGIC)
	{
		pwarn("%s: invalide magic (%x)\n", src);
		close(fd);
		return (0);
	}
	ch->body = ft_salloc(sizeof(t_byte) * ch->header.size);
	read(fd, ch->body, ch->header.size);//TODO: gerer le flux non continue de l'école avec une boucle
	return (1);

}

int				loadChampsDefault(int c, char **av, t_core *core)
{
	int	ac;

	ac = -1;
	while (++ac < c)
	{
		if (core->vm.champ_count++ < MAX_PLAYERS)
		{
			if (!readChampDef(av[ac], core->vm.champ_count, &core->vm.champs[core->vm.champ_count - 1]))
				return (0);
		}
		else
			ft_putendl("4 player max");
	}
	return (1);
}
