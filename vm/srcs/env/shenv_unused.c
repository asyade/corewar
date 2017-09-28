/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shenv_unused.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 13:56:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/28 21:37:31 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_sh.h"
#include "corewar.h"

void		cb_mem_updated(t_memory *m, int a, int b)
{
	(void)m;
	(void)a;
	(void)b;
}

void		cb_live_delta(int del)
{
	(void)del;
}

void		cb_pc_loaded(t_champ *champ)
{
	(void)champ;
}
