/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:35:16 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 13:38:05 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_width(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_wid))
	{
		if (get_double(&(r->o->width), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= g_wid;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_height(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_hei))
	{
		if (get_double(&(r->o->height), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= g_hei;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_negative(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_neg))
	{
		if (get_int(&(r->o->neg), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= g_neg;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_rotation(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_rot))
	{
		if (get_vector(&r->o->rot, v, ROTAT) == ERROR)
			return (ERROR);
		r->o->opt |= g_rot;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_reflection(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_ref) && !is_set(r->o->opt, g_tcp))
	{
		if (get_int(&(r->o->rfl), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= g_ref;
		return (SUCCESS);
	}
	return (ERROR);
}
