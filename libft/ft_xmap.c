#include "libft.h"

static t_xmap	*new_xmap()
{
	t_xmap	*ret;

	ret = ft_salloc(sizeof(t_xmap));
	ret->map = ft_salloc(sizeof(void *) * XMAP_SIZE);
	ret->flags = XF_OCCUPIED;
	ret->size = XMAP_SIZE;
	ret->ptr = 0;
	return (ret);
}

static void		free_xmap(t_xmap *xmap)
{
	if (!xmap)
		return ;
	free(xmap->map);
	free(xmap);
}

static t_xmap	*extend_xmap(t_xmap *map)
{
	void	**new;

	if (!map)
		return (NULL);
	map->size *= 2;
	new = ft_salloc(sizeof(void *) * map->size);
	ft_memcpy(new, map->map, map->ptr * sizeof(void *));
	free(map->map);
	map->map = new;
	return (map);
}

t_xmap			*ft_xmap(int ref, int mode)
{
	static t_xmap	*maps[XMAP_MAX];

	if (mode == XFREE)
	{
		free_xmap(maps[ref]);
		maps[ref] = NULL;
		return (NULL);
	}
	else if (mode == XEXTENDE)
		return (extend_xmap(maps[ref]));
	if (!maps[ref])
		maps[ref] = new_xmap();
	return (maps[ref]);
}
