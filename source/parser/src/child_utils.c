/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:29:06 by hastid            #+#    #+#             */
/*   Updated: 2020/11/12 23:35:32 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_ray(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, RAY_SET))
	{
		if (get_double(&(r->o->ray), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= RAY_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_axis(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, AXI_SET)
			&& get_vector(&r->l->axi, v, NONE))
	{
		r->l->opt |= AXI_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 10 && !IS_SET(r->o->opt, AXI_SET)
			&& get_vector(&r->o->axi, v, NONE))
	{
		r->o->opt |= AXI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_color(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, COL_SET)
			&& get_vector(&r->l->col, v, COLOR))
	{
		r->l->opt |= COL_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 10 && !IS_SET(r->o->opt, COL_SET)
			&& get_vector(&r->o->col, v, COLOR))
	{
		r->o->opt |= COL_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_origin(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, ORI_SET)
			&& get_vector(&r->l->ori, v, NONE))
	{
		r->l->opt |= ORI_SET;
		return (SUCCESS);
	}
	if (r->id == CAMERA && !IS_SET(r->c->opt, ORI_SET)
			&& get_vector(&r->c->ori, v, NONE))
	{
		r->c->opt |= ORI_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 10 && !IS_SET(r->o->opt, ORI_SET)
			&& get_vector(&r->o->ori, v, NONE))
	{
		r->o->opt |= ORI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}
