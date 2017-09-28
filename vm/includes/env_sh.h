/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:29:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/28 21:36:33 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_SH_H
# define ENV_SH_H

# include "corewar.h"

# define BASE_HEX_MAJ	"0123456789abcdef"

t_core		*sh_env(t_core *c);
void		show_consts(t_core *c);
int			inst_count(int opcode);
void		cb_pc_die(t_champ *champ, t_process *pc);
void		cb_player_die(t_champ *champ);
void		cb_cycle_updated(void);
void		cb_pc_updated(t_process *pc);
char		*carry_label(t_process *pc);
void		cb_inst_loaded(t_champ *c, t_process *p);
void		cb_pc_loaded(t_champ *champ);
void		cb_mem_updated(t_memory *m, int a, int b);
void		cb_cycle_to_die_delta(int ctd);
void		cb_player_live(t_champ *c, int id);
void		cb_envdone(t_vm *vm);
void		dump_inst_called(void);
void		cb_live_delta(int del);
void		she_init(t_core *core);

#endif
