#include "corewar.h"
#include <fcntl.h>
#include <sys/types.h>

static int		checkSize(char *nm, int fd, int size)
{
	off_t		real;

	real = lseek(fd, 0, SEEK_END) - sizeof(t_champHeader);
	if (real != size)
	{
		pcri("%s: champ size different from header size\n", nm);
		return (0);
	}
	if (real > CHAMP_MAX_SIZE)
	{
		pcri("%s: champ size too big ( %d > %d )\n", real, CHAMP_MAX_SIZE);
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
	read(fd, ch->body, ch->header.size);
	return (1);
}

int				loadChampsDefault(t_param *p, t_core *core)
{
	int				i;

	i = -1;
	while (++i < p->count)
	{
		if (!readChampDef(p->champs[i].path, p->champs[i].number, &core->vm.champs[i]))
			return (0);
	}
	core->vm.champ_count = p->count;
	return (1);
}
