#include "libft.h"

void			*ft_xalloc(size_t size, int ref)
{
	t_xmap	*map;

	if (!(map = ft_xmap(ref, XGET)))
		exit(1);
	if (map->ptr + 1 < map->size)
	{
		map->map[map->ptr] = ft_salloc(size);
		return (map->map[map->ptr++]);
	}
	ft_xmap(ref, XEXTENDE);
	return (ft_xalloc(size, ref));
}

void			*ft_xcalloc(size_t size, int ref)
{
	void	*ret;

	ret = ft_xalloc(size, ref);
	ft_bzero(ret, size);
	return (ret);
}

void			ft_xfree(void *ptr, int ref)
{
	t_xmap		*map;
	size_t		i;

	if (!(map = ft_xmap(ref, XGET)))
		return ;
	i = map->ptr;
	while (i--)
	{
		if (map->map[i] == ptr)
		{
			map->map[i] = NULL;
			free(ptr);
			return ;
		}
	}
}

void			ft_xclear(int ref)
{
	t_xmap	*map;

	if (!(map = ft_xmap(ref, XGET)))
		return ;
	while (map->ptr--)
	{
		if (map->map[map->ptr])
			free(map->map[map->ptr]);
	}
	ft_xmap(ref, XFREE);
}

t_list				*ft_xlstcreate(void *content, size_t content_size, int ref)
{
	t_list	*lptr;

	lptr = ft_xalloc(sizeof(t_list), ref);
	lptr->content = content;
	lptr->next = NULL;
	lptr->content_size = content_size;
	return (lptr);
}

t_list				*ft_xlstnew(void *content, size_t content_size, int ref)
{
	t_list	*lptr;

	lptr = ft_xalloc(sizeof(t_list), ref);
	lptr->content = ft_xalloc(content_size, ref);
	ft_memcpy(lptr->content, content, content_size);
	lptr->next = NULL;
	lptr->content_size = content_size;
	return (lptr);
}
