/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:28:10 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 10:39:00 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	solve_equation_neg(t_delt d, double t_min, double t_max)
{
	double	t1;
	double	t2;
	double	delta;

	delta = d.b * d.b - 4 * d.a * d.c;
	if (delta < 0 || d.a == 0)
		return (t_min);
	t1 = (-d.b - sqrt(delta)) / (2 * d.a);
	t2 = (-d.b + sqrt(delta)) / (2 * d.a);
	if (t1 < MIN_NBR && t2 < MIN_NBR)
		return (t_min);
	if ((t_min > fmin(t1, t2) && t_min < fmax(t1, t2)))
		return ((t1 < t_max && t2 < t_max) ? t_max : 0);
	return (t_min);
}

double	intersect_cone_neg(t_ray r, t_obj *obj, double t_min, double t_max)
{
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir) - (1 + pow(tan(RAD(obj->ray)), 2)) *
										pow(ft_vect_dot(r.dir, obj->axi), 2);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
			* ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi));
	d.c = ft_vect_dot(obj_center, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
				* pow(ft_vect_dot(obj_center, obj->axi), 2);
	return (solve_equation_neg(d, t_min, t_max));
}

double	intersect_sphere_neg(t_ray r, t_obj *obj, double t_min, double t_max)
{
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir);
	d.b = 2 * ft_vect_dot(r.dir, obj_center);
	d.c = ft_vect_dot(obj_center, obj_center) - obj->ray * obj->ray;
	return (solve_equation_neg(d, t_min, t_max));
}

double	intersect_cylinder_neg(t_ray r, t_obj *obj, double t_min, double t_max)
{
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
	return ((solve_equation_neg(d, t_min, t_max)));
}

double	negative_objects(double t_min, t_ray r, double t_max, t_rt *rt)
{
	int		i;
	double	dist;
	t_obj	*obj;

	i = 0;
	obj = rt->o;
	if (!(dist = t_min))
		return (0);
	while (obj)
	{
		if (obj->neg)
		{
			if (obj->id == CONE)
				dist = intersect_cone_neg(r, obj, t_min, t_max);
			else if (obj->id == SPH)
				dist = intersect_sphere_neg(r, obj, t_min, t_max);
			else if (obj->id == CYL)
				dist = intersect_cylinder_neg(r, obj, t_min, t_max);
		}
		if (dist != t_min)
			return (dist);
		obj = obj->next;
	}
	return (dist);
}
