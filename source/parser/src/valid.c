/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:56:51 by hastid            #+#    #+#             */
/*   Updated: 2020/03/01 04:58:03 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	object_is_valid(int opt, int t)
{
	if (t == CONE || t == PLANE || t == SPHERE || t == CYLINDER)
	{
		if (!IS_SET(opt, ORI_SET))
			return (ERROR);
		if (!IS_SET(opt, COL_SET))
			return (ERROR);
		if (!IS_SET(opt, AXI_SET))
			return (ERROR);
		if (!IS_SET(opt, ROT_SET))
			return (ERROR);
		if (!IS_SET(opt, TRA_SET))
			return (ERROR);
		if (t != PLANE && !IS_SET(opt, RAY_SET))
			return (ERROR);
		return (SUCCESS);
	}
	return (ERROR);
}

int	objects_is_valid(t_obj *o)
{
	t_obj *tmp;

	if (!o)
		return (ERROR);
	tmp = o;
	while (tmp)
	{
		if (!object_is_valid(tmp->opt, o->id))
			return (ERROR);
		tmp->ori = ft_vect_add(tmp->ori, tmp->tra);
		tmp->axi = ft_vect_rotate(tmp->axi, tmp->rot);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	light_is_valid(int opt)
{
	if (!IS_SET(opt, ORI_SET))
		return (ERROR);
	if (!IS_SET(opt, COL_SET))
		return (ERROR);
	if (!IS_SET(opt, POW_SET))
		return (ERROR);
	return (SUCCESS);
}

int	lights_is_valid(t_light *l)
{
	t_light *tmp;

	if (!l)
		return (ERROR);
	tmp = l;
	while (tmp)
	{
		if (!light_is_valid(tmp->opt))
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	camera_is_valid(t_cam *c)
{
	if (!c)
		return (ERROR);
	if (!IS_SET(c->opt, ORI_SET))
		return (ERROR);
	if (!IS_SET(c->opt, TAR_SET))
		return (ERROR);
	if (!IS_SET(c->opt, FOV_SET))
		return (ERROR);
	return (SUCCESS);
}

int	data_is_valid(t_rt *r)
{
	if (!camera_is_valid(r->c))
		return (ERROR);
	if (!lights_is_valid(r->l))
		return (ERROR);
	if (!objects_is_valid(r->o))
		return (ERROR);
	return (SUCCESS);
}
