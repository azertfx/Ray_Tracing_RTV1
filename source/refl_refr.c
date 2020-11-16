/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refl_refr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:24:54 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/11/16 03:06:24 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	obj_reflection(t_vect ray_dir, t_vect p_normal)
{
	return (ft_vect_add(ray_dir, ft_vect_mult_nbr(p_normal,
			(2 * (-1 * ft_vect_dot(p_normal, ray_dir))))));
}

t_vect	obj_refraction(t_vect ray_dir, t_vect p_normal)
{
	double ior;
	double cost1;
	double cost2;

	ior = 1.0 / 1.0;
	cost1 = ft_vect_dot(p_normal, ft_vect_mult_nbr(ray_dir, -1));
	cost2 = 1 - ior * ior * (1 - cost1 * cost1);
	if (cost2 >= 0)
	{
		cost2 = sqrtf(cost2);
		if (cost1 >= 0)
			cost2 = -cost2;
		return (ft_vect_add(ft_vect_mult_nbr(ray_dir, ior),
				ft_vect_mult_nbr(p_normal, ior * cost1 + cost2)));
	}
	return (ray_dir);
}

void	check_refl_refr(t_rt *v, t_ray *ray, t_vect *depth)
{
	if (v->point.obj->rfl)
	{
		ray->dir = obj_reflection(ray->dir, v->point.p_normal);
		depth->y = v->point.obj->rfl;
		depth->z = 0;
	}
	if (v->point.obj->trs)
	{
		ray->dir = obj_refraction(ray->dir, v->point.p_normal);
		depth->z = v->point.obj->trs;
		depth->y = 0;
	}
}
