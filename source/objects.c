/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:27:32 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/04 02:42:10 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	sphere_intersection(t_ray r, t_obj *obj)
{
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir);
	d.b = 2 * ft_vect_dot(r.dir, obj_center);
	d.c = ft_vect_dot(obj_center, obj_center) - obj->ray * obj->ray;
	return (equation_solve(r, d, obj));
}

double	cylinder_intersection(t_ray r, t_obj *obj)
{
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	d.a = ft_vect_dot(r.dir, r.dir) - ft_vect_dot(r.dir, obj->axi) *
												ft_vect_dot(r.dir, obj->axi);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) -
	(ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi)));
	d.c = ft_vect_dot(obj_center, obj_center) -
			ft_vect_dot(obj_center, obj->axi) *
						ft_vect_dot(obj_center, obj->axi) - obj->ray * obj->ray;
	return (equation_solve(r, d, obj));
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
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	d.a = ft_vect_dot(r.dir, r.dir) - (1 + pow(tan(RAD(obj->ray)), 2)) *
										pow(ft_vect_dot(r.dir, obj->axi), 2);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
			* ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi));
	d.c = ft_vect_dot(obj_center, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
				* pow(ft_vect_dot(obj_center, obj->axi), 2);
	return (equation_solve(r, d, obj));
}
