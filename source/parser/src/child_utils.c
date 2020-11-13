/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:29:06 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 13:38:05 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_ray(t_rt *r, char *v)
{
	if (!is_set(r->o->opt, g_ray))
	{
		if (get_double(&(r->o->ray), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= g_ray;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_axis(t_rt *r, char *v)
{
	if (r->id == LIGHT && !is_set(r->l->opt, g_axi)
			&& get_vector(&r->l->axi, v, NONE))
	{
		r->l->opt |= g_axi;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 10 && !is_set(r->o->opt, g_axi)
			&& get_vector(&r->o->axi, v, NONE))
	{
		r->o->opt |= g_axi;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_color(t_rt *r, char *v)
{
	if (r->id == LIGHT && !is_set(r->l->opt, g_col)
			&& get_vector(&r->l->col, v, COLOR))
	{
		r->l->opt |= g_col;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 10 && !is_set(r->o->opt, g_col)
			&& get_vector(&r->o->col, v, COLOR))
	{
		r->o->opt |= g_col;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_origin(t_rt *r, char *v)
{
	if (r->id == LIGHT && !is_set(r->l->opt, g_ori)
			&& get_vector(&r->l->ori, v, NONE))
	{
		r->l->opt |= g_ori;
		return (SUCCESS);
	}
	if (r->id == CAMERA && !is_set(r->c->opt, g_ori)
			&& get_vector(&r->c->ori, v, NONE))
	{
		r->c->opt |= g_ori;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 10 && !is_set(r->o->opt, g_ori)
			&& get_vector(&r->o->ori, v, NONE))
	{
		r->o->opt |= g_ori;
		return (SUCCESS);
	}
	return (ERROR);
}
