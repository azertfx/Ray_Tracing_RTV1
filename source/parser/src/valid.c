/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:56:51 by hastid            #+#    #+#             */
/*   Updated: 2020/11/06 01:22:51 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	object_is_valid(int opt, int t)
{
	if (t >= 2 && t <= 8)
	{
		if (!IS_SET(opt, ORI_SET))
			return (ERROR);
		if (!IS_SET(opt, COL_SET))
			return (ERROR);
		if (!IS_SET(opt, ROT_SET))
			return (ERROR);
		if (!IS_SET(opt, TRA_SET))
			return (ERROR);
		if (t != PLANE && t != SQUARE && !IS_SET(opt, RAY_SET))
			return (ERROR);
		if (t != SPHERE && !IS_SET(opt, AXI_SET))
			return (ERROR);
		if (t == SQUARE && (!IS_SET(opt, LM1_SET) || !IS_SET(opt, LM2_SET)))
			return (ERROR);
		if (IS_SET(opt, SLC_SET))
			if (!IS_SET(opt, UOD_SET) || !IS_SET(opt, LIM_SET))
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
		ft_vect_norm(&tmp->axi);
		tmp = tmp->next;
	}
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
		if (!IS_SET(tmp->opt, ORI_SET))
			return (ERROR);
		if (!IS_SET(tmp->opt, COL_SET))
			return (ERROR);
		if (!IS_SET(tmp->opt, POW_SET))
			return (ERROR);
		if (tmp->id == DIRECT && !IS_SET(tmp->opt, AXI_SET))
			return (ERROR);
		if (tmp->id == DIRECT && !IS_SET(tmp->opt, ANG_SET))
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
