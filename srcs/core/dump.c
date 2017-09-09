#include "corewar.h"

#define	DUMP_OPL	64 //32 selon le pdf
#define DUMP_LSIZE	(DUMP_OPL + (DUMP_OPL * 2) + (11 * DUMP_OPL))
#define DUMP_BASE	"0123456789abcdef"

static void	fill_line(char *buff, t_byte *ptr, int n)
{
	while (n--)
	{	
		*buff++ = DUMP_BASE[*ptr / 16];
		*buff++ = DUMP_BASE[*ptr++ % 16];
		*buff++ = ' ';
	}
	*buff = '\0';
}

static void	dump_line(t_byte *ptr, t_vptr v, int n)
{
	char	buff[DUMP_LSIZE];

	fill_line(buff + sprintf(buff, "0x%4.4x : ", (unsigned)v), ptr, n);
	ft_putendl(buff);
}

void		dump(t_vm *vm)
{
	t_vptr	curr;

	curr = 0;
	while (curr < MEM_SIZE)
	{
		dump_line(vm->memory.mem + curr, curr, DUMP_OPL);
		curr += DUMP_OPL;
	}
	exit(0);
}
