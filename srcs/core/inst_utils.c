/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <acorbeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:30:01 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/17 18:30:02 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_byte   pchk(t_byte p[3], t_byte code, t_int32 val)
{
    t_byte      x;

    x = -1;
    if (!p && !code)
        return (1);
    if (!p && code)
    {
        pwarn("too many parametters !\n");
        return (0);
    }
    if (p && !code)
    {
        pwarn("undefined parametters !\n");
        return (0);
    }
    if (code == T_REG && (val <= 0 || val >= 17))
    {
        pwarn("invalide register !\n");
        return (0);
    }
    while (++x < 3)
    {
        if (p[x] == code)
            return (1);
    }
    pwarn("invalide parametters !\n");
    return (0);
}

static t_byte   getit(t_process *pc, t_byte pid)
{
    t_byte     t;

    t = 0;
    if (pid == 1)
        t = IP1(pc->inst[1]);
    else if (pid == 2)
        t = IP2(pc->inst[1]);
    else if (pid == 3)
        t = IP3(pc->inst[1]);
    else if (pid == 4)
        t = IP4(pc->inst[1]);
    return (t);
}

t_int32         param_val(t_vm *vm, t_process *pc, t_byte pid)
{
    t_byte     t;

    t = getit(pc, pid);
    if (t == T_DIR)
        return (pc->inst[pid + 1]);
    else if (t == T_IND)
        return (mem_readint(&vm->memory, IDXPTR(pc->cc, pc->inst[pid + 1])));//on pars de pc ou cc?
    else if (t == T_REG)
        return (pc->reg[pc->inst[pid + 1] - 1]);
    return (-1);
}

t_int32         param_dirval(t_process *pc, t_byte pid)
{
    t_byte     t;

    t = getit(pc, pid);
    if (t == T_DIR || t == T_IND)
        return (pc->inst[pid + 1]);
    else if (t == T_REG)
    {
        return (pc->reg[pc->inst[pid + 1] - 1]);
    }
    return (-1);
}

t_byte          params_chk(t_byte a[3], t_byte b[3], t_byte c[3], t_byte d[3], t_int32 inst[6])
{
    if (!a && !b && !c && !d)
        return (!(inst[2]));
    if (!pchk(a, IP1(inst[1]), inst[2]))
        return (0);
    if (!pchk(b, IP2(inst[1]), inst[3]))
        return (0);
    if (!pchk(c, IP3(inst[1]), inst[4]))
        return (0);
    if (!pchk(d, IP4(inst[1]), inst[5]))
        return (0);
    return (1);
}
