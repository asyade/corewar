#include "corewar.h"

/*
** Compare l'octet d'encodage avec le t_arg_type corespondant
** Attentions T_XXX != FT_XXX, si non on a un conflit d'encodage
*/

t_int32		params_match(t_byte a, t_arg_type b)
{
	if (a == 0 && b)
		return (0);
	if (b == 0 && a)
		return (0);
	if (a == T_IND && b & FT_IND)
		return (1);
	if (a == T_DIR && b & FT_DIR)
		return (1);
	if (a == T_REG && b & FT_REG)
		return (1);
	return (0);
}

/*
** Fais avancer le pc du nombre presumer de paramettres
*/

t_int32		params_correct(t_process *pc)
{
	t_int32		i;

	i = op_tab[pc->inst[0] - 1].nbr_arg;
	if (i >= 1)
		pc->pc += param_get_size(pc->inst[0], IP1(pc->inst[1]));
	if (i >= 2)
		pc->pc += param_get_size(pc->inst[0], IP2(pc->inst[1]));
	if (i >= 3)
		pc->pc += param_get_size(pc->inst[0], IP3(pc->inst[1]));
	if (i >= 4)
		pc->pc += param_get_size(pc->inst[0], IP4(pc->inst[1]));
	return (0);
}

/*
** Verifis les paramettre un par un en comparans avec optab
** En cas de paramettre invalide on avance le pc
*/

t_int32		params_check_correct(t_process *pc)
{
	t_op	*mask;

	mask = &op_tab[pc->inst[0] - 1];
	if (mask->nbr_arg >= 1 && !params_match(IP1(pc->inst[1]), mask->arg_type[0]))
		return (params_correct(pc));
	if (mask->nbr_arg >= 2 && !params_match(IP2(pc->inst[1]), mask->arg_type[1]))
		return (params_correct(pc));
	if (mask->nbr_arg >= 3 && !params_match(IP3(pc->inst[1]), mask->arg_type[2]))
		return (params_correct(pc));
	if (mask->nbr_arg >= 4 && !params_match(IP4(pc->inst[1]), mask->arg_type[3]))
		return (params_correct(pc));
	return (1);
}

t_int32		params_check_register(t_process *pc)
{
	if (op_tab[pc->inst[0] - 1].octal_code == 0)
	{
		if (op_tab[pc->inst[0] - 1].arg_type[0] == T_REG)
			return (REGVALIDE(pc->inst[1]));
		else
			return (0);
	}
	if (
		(IP1(pc->inst[1]) == T_REG && !REGVALIDE(pc->inst[2])) ||
		(IP2(pc->inst[1]) == T_REG && !REGVALIDE(pc->inst[3])) ||
		(IP3(pc->inst[1]) == T_REG && !REGVALIDE(pc->inst[4])) ||
		(IP4(pc->inst[1]) == T_REG && !REGVALIDE(pc->inst[5]))
	)
		return (0);
	return (1);
}