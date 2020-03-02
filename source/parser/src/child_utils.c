/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:29:06 by hastid            #+#    #+#             */
/*   Updated: 2020/03/01 04:30:44 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_ray(t_rt *r, char *v)
{
	if (r->id >= 2 && r->id <= 5 && !IS_SET(r->o->opt, RAY_SET)
			&& get_double(&(r->o->ray), v, RAY))
	{
		r->o->opt |= RAY_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_fov(t_rt *r, char *v)
{
	if (r->id == CAMERA && !IS_SET(r->c->opt, FOV_SET)
			&& get_double(&(r->c->fov), v, FOV))
	{
		r->c->opt |= FOV_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_power(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, POW_SET)
			&& get_double(&(r->l->pow), v, POWER))
	{
		r->l->opt |= POW_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_origin(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, ORI_SET)
			&& get_vect(&r->l->ori, v, ORIGIN))
	{
		r->l->opt |= ORI_SET;
		return (SUCCESS);
	}
	if (r->id == CAMERA && !IS_SET(r->c->opt, ORI_SET)
			&& get_vect(&r->c->ori, v, ORIGIN))
	{
		r->c->opt |= ORI_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 5 && !IS_SET(r->o->opt, ORI_SET)
			&& get_vect(&r->o->ori, v, ORIGIN))
	{
		r->o->opt |= ORI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_target(t_rt *r, char *v)
{
	if (r->id == CAMERA && !IS_SET(r->c->opt, TAR_SET)
			&& get_vect(&r->c->tar, v, ORIGIN))
	{
		r->c->opt |= TAR_SET;
		return (SUCCESS);
	}
	return (ERROR);
}
