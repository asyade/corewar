/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 23:27:26 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void		vm_kill_sound(void)
{
	static int	count = KILL_INTERVAL;

	if (count-- > 0)
		return ;
	count = KILL_INTERVAL;
	system("afplay ./sounds/mouse.mp3 2>-");
}

void		vm_live_sound(void)
{
	static int	count = LIVE_INTERVAL;

	if (count-- > 0)
		return ;
	count = LIVE_INTERVAL;
	system("afplay ./sounds/mouse.wav 2>-");
}

void		vm_jump_sound(void)
{
	static int	count = JUMP_INTERVAL;

	if (count-- > 0)
		return ;
	count = JUMP_INTERVAL;
	system("afplay ./sounds/jump.wav 2>-");
}

void		*vm_play_ambient(void *p)
{
	system("afplay ./sounds/end.mwav ");
	return (p);
}

void		vm_sound_ambient(int stop)
{
	(void)stop;
}
