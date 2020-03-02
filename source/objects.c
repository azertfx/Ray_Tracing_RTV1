/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:27:32 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/27 23:37:36 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	equation_solve(double a, double b, double c)
{
	double	delta;
	double	inter1;
	double	inter2;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	inter1 = (-b - sqrt(delta)) / (2 * a);
	inter2 = (-b + sqrt(delta)) / (2 * a);
	if ((inter2 < MIN_NBR && inter1 < MIN_NBR))
		return (0);
	if ((inter2 < MIN_NBR))
		return (inter1);
	if ((inter1 < MIN_NBR))
		return (inter2);
	return (fmin(inter1, inter2));
}

double	sphere_intersection(t_ray r, t_obj *obj)
{
	double		a;
	double		b;
	double		c;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	a = ft_vect_dot(r.dir, r.dir);
	b = 2 * ft_vect_dot(r.dir, obj_center);
	c = ft_vect_dot(obj_center, obj_center) - obj->ray * obj->ray;
	return (equation_solve(a, b, c));
}

double	cylinder_intersection(t_ray r, t_obj *obj)
{
	double		a;
	double		b;
	double		c;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	a = ft_vect_dot(r.dir, r.dir) - ft_vect_dot(r.dir, obj->axi) *
												ft_vect_dot(r.dir, obj->axi);
	b = 2 * (ft_vect_dot(r.dir, obj_center) -
	(ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi)));
	c = ft_vect_dot(obj_center, obj_center) -
			ft_vect_dot(obj_center, obj->axi) *
						ft_vect_dot(obj_center, obj->axi) - obj->ray * obj->ray;
	return (equation_solve(a, b, c));
}

double	plane_intersection(t_ray r, t_obj *obj)
{
	t_vect	obj_center;
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
	double		a;
	double		b;
	double		c;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	a = ft_vect_dot(r.dir, r.dir) - (1 + pow(tan(obj->ray), 2)) *
										pow(ft_vect_dot(r.dir, obj->axi), 2);
	b = 2 * (ft_vect_dot(r.dir, obj_center) - (1 + pow(tan(obj->ray), 2)) *
		ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi));
	c = ft_vect_dot(obj_center, obj_center) - (1 + pow(tan(obj->ray), 2)) *
								pow(ft_vect_dot(obj_center, obj->axi), 2);
	return (equation_solve(a, b, c));
}
