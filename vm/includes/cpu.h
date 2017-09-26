/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 00:10:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/26 09:52:16 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H

# define AXO_ARG	(FT_REG | FT_DIR | FT_IND)

# define T_ARG_TP	t_arg_type[]
# define ARG_LIVE	(T_ARG_TP){FT_DIR, 0, 0, 0}
# define ARG_LD		(T_ARG_TP){FT_DIR | FT_IND, FT_REG, 0, 0}
# define ARG_ST		(T_ARG_TP){FT_REG, FT_IND | FT_REG, 0, 0}
# define ARG_ADD	(T_ARG_TP){FT_REG, FT_REG, FT_REG, 0}
# define ARG_SUB	(T_ARG_TP){FT_REG, FT_REG, FT_REG, 0}
# define ARG_AND	(T_ARG_TP){AXO_ARG, FT_REG | FT_IND | FT_DIR, FT_REG, 0}
# define ARG_OR		(T_ARG_TP){AXO_ARG, FT_REG | FT_IND | FT_DIR, FT_REG, 0}
# define ARG_XOR	(T_ARG_TP){AXO_ARG, FT_REG | FT_IND | FT_DIR, FT_REG, 0}
# define ARG_ZJMP	(T_ARG_TP){FT_DIR, 0, 0, 0}
# define ARG_LDI	(T_ARG_TP){AXO_ARG, FT_DIR | FT_REG, FT_REG, 0}
# define ARG_STI	(T_ARG_TP){FT_REG, AXO_ARG, FT_DIR | FT_REG, 0}
# define ARG_FORK	(T_ARG_TP){FT_DIR, 0, 0, 0}
# define ARG_LLD	(T_ARG_TP){FT_DIR | FT_IND, FT_REG, 0, 0}
# define ARG_LLDI	(T_ARG_TP){AXO_ARG, FT_DIR | FT_REG, FT_REG, 0}
# define ARG_LFORK	(T_ARG_TP){FT_DIR, 0, 0, 0}
# define ARG_AFF	(T_ARG_TP){FT_REG, 0, 0, 0}

t_int16	params_count(t_byte op);
t_int32	update_invalide_pc(t_process *pc);

void	cpu_pc_process(t_vm *vm, int ci, t_process *pc);
void	cpu_process_cycle(t_vm *vm);

#endif
