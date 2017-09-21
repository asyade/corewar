#include <stdlib.h>

void		vm_kill_sound(void)
{
	system("mpg123 -q mouse.mp3 &");
}