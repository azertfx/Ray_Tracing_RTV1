/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:38:23 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 09:42:23 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_translation(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, TRA_SET))
	{
		if (get_vector(&r->o->tra, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= TRA_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_transparence(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, TCP_SET) && !IS_SET(r->o->opt, REF_SET))
	{
		if (get_int(&(r->o->trs), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= TCP_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_slice(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, SLC_SET))
	{
		if (get_int(&(r->o->slc), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= SLC_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_limit(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, LIM_SET))
	{
		if (get_vector(&r->o->lim, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= LIM_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_upordown(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, UOD_SET))
	{
		if (get_int(&(r->o->uod), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= UOD_SET;
		return (SUCCESS);
	}
	return (ERROR);
}
