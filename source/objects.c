/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:27:32 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/13 10:39:45 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	sphere_intersection(t_ray r, t_obj *obj)
{
	t_delt	d;
	double	m;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir);
	d.b = 2 * ft_vect_dot(r.dir, obj_center);
	d.c = ft_vect_dot(obj_center, obj_center) - obj->ray * obj->ray;
	if (obj->height < 0)
		return (equation_solve(r, d, obj));
	d.t = equation_solve(r, d, obj);
	if (d.t && obj->height >= 0)
	{
		m = ft_vect_dot(r.dir, obj->axi) * d.t
										+ ft_vect_dot(obj_center, obj->axi);
		if (!(m <= obj->height / 2))
			return (0);
	}
	return (d.t);
}

double	cylinder_intersection(t_ray r, t_obj *obj)
{
	double	m;
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir) - ft_vect_dot(r.dir, obj->axi) *
												ft_vect_dot(r.dir, obj->axi);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) -
	(ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi)));
	d.c = ft_vect_dot(obj_center, obj_center) -
			ft_vect_dot(obj_center, obj->axi) *
						ft_vect_dot(obj_center, obj->axi) - obj->ray * obj->ray;
	if (obj->height < 0)
		return (equation_solve(r, d, obj));
	d.t = equation_solve(r, d, obj);
	if (d.t && obj->height >= 0)
	{
		m = ft_vect_dot(r.dir, obj->axi) * d.t
										+ ft_vect_dot(obj_center, obj->axi);
		if (!(m <= obj->height / 2 && m >= -obj->height / 2))
			return (0);
	}
	return (d.t);
}

double	plane_intersection(t_ray r, t_obj *obj)
{
	t_vect		obj_center;
	double		inter;
	double		nor_dir;

	obj_center = ft_vect_sub(obj->ori, r.ori);
	if ((nor_dir = ft_vect_dot(r.dir, obj->axi)))
		inter = ft_vect_dot(obj_center, obj->axi) / nor_dir;
	else
		return (0);
	if (inter < MIN_NBR || inter > MAX_NBR)
		return (0);
	return (inter + MIN_NBR);
}

double	cone_intersection(t_ray r, t_obj *obj)
{
	double	m;
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir) - (1 + pow(tan(RAD(obj->ray)), 2)) *
										pow(ft_vect_dot(r.dir, obj->axi), 2);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
			* ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi));
	d.c = ft_vect_dot(obj_center, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
				* pow(ft_vect_dot(obj_center, obj->axi), 2);
	if (obj->height < 0)
		return (equation_solve(r, d, obj));
	d.t = equation_solve(r, d, obj);
	if (d.t && obj->height >= 0)
	{
		m = ft_vect_dot(r.dir, obj->axi) * d.t
									+ ft_vect_dot(obj_center, obj->axi);
		if (!(m <= 0 && m >= -obj->height))
			return (0);
	}
	return (d.t);
}

double	paraboloid_intersection(t_ray r, t_obj *parab)
{
	t_delt	d;
	t_vect	v;
	double	a;
	double	b;

	v = ft_vect_sub(r.ori, parab->ori);
	a = ft_vect_dot(r.dir, parab->axi);
	b = ft_vect_dot(v, parab->axi);
	d.a = ft_vect_dot(r.dir, r.dir) - a * a;
	d.b = 2 * (ft_vect_dot(r.dir, v) - (a * (b + 2 * parab->ray)));
	d.c = ft_vect_dot(v, v) - b * (b + 4 * parab->ray);
	return (equation_solve(r, d, parab));
}
