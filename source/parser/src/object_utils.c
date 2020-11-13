/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:35:16 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 09:42:30 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_width(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, WID_SET))
	{
		if (get_double(&(r->o->width), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= WID_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_height(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, HEI_SET))
	{
		if (get_double(&(r->o->height), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= HEI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_negative(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, NEG_SET))
	{
		if (get_int(&(r->o->neg), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= NEG_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_rotation(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, ROT_SET))
	{
		if (get_vector(&r->o->rot, v, ROTAT) == ERROR)
			return (ERROR);
		r->o->opt |= ROT_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_reflection(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, REF_SET) && !IS_SET(r->o->opt, TCP_SET))
	{
		if (get_int(&(r->o->rfl), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= REF_SET;
		return (SUCCESS);
	}
	return (ERROR);
}
