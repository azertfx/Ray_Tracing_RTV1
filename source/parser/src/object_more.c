/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:38:23 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 13:38:05 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_translation(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_tra))
	{
		if (get_vector(&r->o->tra, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= g_tra;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_transparence(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_tcp) && !is_set(r->o->opt, g_ref))
	{
		if (get_int(&(r->o->trs), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= g_tcp;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_slice(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_slc))
	{
		if (get_int(&(r->o->slc), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= g_slc;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_limit(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_lim))
	{
		if (get_vector(&r->o->lim, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= g_lim;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_upordown(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_uod))
	{
		if (get_int(&(r->o->uod), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= g_uod;
		return (SUCCESS);
	}
	return (ERROR);
}
