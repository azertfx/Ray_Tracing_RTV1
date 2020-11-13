/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:56:51 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 13:38:05 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	object_is_valid(int opt, int t)
{
	if (t >= 2 && t <= 10)
	{
		if (!is_set(opt, g_ori))
			return (ERROR);
		if (!is_set(opt, g_col))
			return (ERROR);
		if (!is_set(opt, g_rot))
			return (ERROR);
		if (!is_set(opt, g_tra))
			return (ERROR);
		if (t != PLA && t != SQUAR && !is_set(opt, g_ray))
			return (ERROR);
		if (t != SPH && !is_set(opt, g_axi))
			return (ERROR);
		if (t == SQUAR && (!is_set(opt, g_lmo) || !is_set(opt, g_lmt)))
			return (ERROR);
		if (is_set(opt, g_slc))
			if (!is_set(opt, g_uod) || !is_set(opt, g_lim))
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
		if (!is_set(tmp->opt, g_ori))
			return (ERROR);
		if (!is_set(tmp->opt, g_col))
			return (ERROR);
		if (!is_set(tmp->opt, g_pow))
			return (ERROR);
		if (tmp->id == DIRECT && !is_set(tmp->opt, g_axi))
			return (ERROR);
		if (tmp->id == DIRECT && !is_set(tmp->opt, g_ang))
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	camera_is_valid(t_cam *c)
{
	if (!c)
		return (ERROR);
	if (!is_set(c->opt, g_ori))
		return (ERROR);
	if (!is_set(c->opt, g_tar))
		return (ERROR);
	if (!is_set(c->opt, g_fov))
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
