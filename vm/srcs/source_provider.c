/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_provider.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/30 03:59:23 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include <sys/types.h>

static int		check_size(char *nm, int fd, int size)
{
	off_t		real;

	real = lseek(fd, 0, SEEK_END) - sizeof(t_champ_header);
	if (real != size)
	{
		ft_printf("error: %s: champ size different from header size\n", nm);
		return (0);
	}
	if (real > CHAMP_MAX_SIZE)
	{
		ft_printf("error: %s: champ size too big ( %d > %d )\n",
nm, real, CHAMP_MAX_SIZE);
		return (0);
	}
	lseek(fd, -real, SEEK_CUR);
	return (1);
}

static int		read_champ_def(char *src, int i, t_champ *ch)
{
	t_int32		fd;

	if (!(fd = open(src, O_RDONLY)))
		return (0);
	if (read(fd, &ch->header, sizeof(t_champ_header)) < 0)
	{
		ft_printf("error: %s: file not found\n", src);
		return (0);
	}
	ch->header.magic = BSWAP32(ch->header.magic);
	ch->header.size = BSWAP32(ch->header.size);
	ch->header.name[PROG_NAME_LEN] = '\0';
	ch->header.comment[COMMENT_LEN] = '\0';
	ch->number = i;
	if (!check_size(src, fd, ch->header.size))
		return (0);
	if (ch->header.magic != COREWAR_MAGIC)
	{
		ft_printf("error: %s: invalide magic (%x)\n", src);
		close(fd);
		return (0);
	}
	ch->body = ft_salloc(sizeof(t_byte) * ch->header.size);
	read(fd, ch->body, ch->header.size);
	return (1);
}

int				load_champs_default(t_param *p, t_core *core)
{
	int				i;

	champs_sort(&core->vm);
	i = -1;
	while (++i < p->count)
	{
		if (!read_champ_def(p->champs[i].path,
				p->champs[i].number, &core->vm.champs[i]))
			return (0);
		core->vm.champs[i].index = i + 1;
	}
	core->vm.champ_count = p->count;
	return (1);
}
