/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/29 04:15:30 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void		vm_kill_sound(void)
{
	system("afplay ./sounds/mouse.mp3 2>-");
}

void		vm_live_sound(void)
{
	system("afplay ./sounds/mouse.wav 2>-");
}

void		vm_jump_sound(void)
{
	system("afplay ./sounds/jump.wav 2>-");
}

void		*vm_play_ambient(void *p)
{
	system("afplay ./sounds/ambient.mp3 ");
	return (p);
}

void		vm_sound_ambient(int stop)
{
	(void)stop;
}
