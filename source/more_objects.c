/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 01:00:56 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/03 06:23:41 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

double		Disc_intersection(t_ray r, t_obj *obj)
{
	t_vect	obj_center;
	double		inter;
	double		nor_dir;
	t_delt		d;

	obj_center = ft_vect_sub(obj->ori, r.ori);
	if ((nor_dir = ft_vect_dot(r.dir, obj->axi)))
		inter = ft_vect_dot(obj_center, obj->axi) / nor_dir;
	else
		return (0);
	if (inter < MIN_NBR || inter > MAX_NBR)
		return (0);
	t_vect p = ft_vect_add(r.ori, ft_vect_mult_nbr(r.dir, inter));
	d.v = ft_vect_sub(obj->ori, p);
	d.t = ft_vect_dot(d.v, d.v);
	if (sqrtf(d.t) <= obj->ray)
		return (inter + MIN_NBR);
	else
		return (0);
}

double		square_intersection(t_ray r, t_obj *obj)
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
	t_vect p = ft_vect_add(r.ori, ft_vect_mult_nbr(r.dir, inter));
	p = ft_vect_sub(p, obj->ori);
	t_vect e1 = {7,0,0};
	t_vect e2 = {0,-7,0};
	double width = ft_vect_length(e1),height = ft_vect_length(e2);
	double proj1 = ft_vect_dot(p, e1)/ width, proj2 = ft_vect_dot(p, e2)/ height;
	if ((proj1 < width && proj1 > 0) && (proj2 < height && proj2 > 0))
		return (inter + MIN_NBR);
	return (0);
}

double		limited_cone_intersection(t_ray r, t_obj *obj)
{
	t_delt	d;
	double	m;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	d.a = ft_vect_dot(r.dir, r.dir) - (1 + pow(tan(RAD(obj->ray)), 2)) *
										pow(ft_vect_dot(r.dir, obj->axi), 2);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
		* ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi));
	d.c = ft_vect_dot(obj_center, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2))
				* pow(ft_vect_dot(obj_center, obj->axi), 2);
	d.t = equation_solve(r, d.a, d.b, d.c, obj);
	if (d.t)
	{
		m = ft_vect_dot(r.dir, obj->axi) * d.t
									+ ft_vect_dot(obj_center, obj->axi);
		if (m <= 0 && m >= -30)
			return (d.t);
	}
	return (0);
}

double		limited_cylinder_intersection(t_ray r, t_obj *obj)
{
	t_delt		d;
	double		m;
	t_vect		obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	d.a = ft_vect_dot(r.dir, r.dir) - ft_vect_dot(r.dir, obj->axi) *
												ft_vect_dot(r.dir, obj->axi);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) -
	(ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi)));
	d.c = ft_vect_dot(obj_center, obj_center) -
			ft_vect_dot(obj_center, obj->axi) *
						ft_vect_dot(obj_center, obj->axi) - obj->ray * obj->ray;
	d.t = equation_solve(r, d.a, d.b, d.c, obj);
	if (d.t)
	{
		m = ft_vect_dot(r.dir, obj->axi) * d.t
										+ ft_vect_dot(obj_center, obj->axi);
		if (m <= 30 && m >= -30)
			return (d.t);
	}
	return (0);
}

double		check_solution(double t1, double t2)
{
	double	t;

	t = 0;
	if (t1 < 0.0)
		t1 = t2;
	if (t2 < 0.0)
		t2 = t1;
	t = fmax(t1, t2);
	if (t > MIN_NBR)
		return (t);
	return (0);
}

double		hemisphere_intersection(t_ray r, t_obj *obj)
{
	t_delt	d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir);
	d.b = 2 * ft_vect_dot(r.dir, obj_center);
	d.c = ft_vect_dot(obj_center, obj_center) - obj->ray * obj->ray;
	d.delta = d.b * d.b - 4 * d.a * d.c;
	if (d.delta < 0)
		return (0);
	d.t1 = (-d.b - sqrt(d.delta)) / (2 * d.a);
	d.t2 = (-d.b + sqrt(d.delta)) / (2 * d.a);
	d.v = ft_vect_add(r.ori, ft_vect_sub(ft_vect_mult_nbr(r.dir, d.t1),
	obj->ori));
	if (ft_vect_dot(obj->axi, d.v) > 0.0)
		d.t1 = -1.0;
	d.v = ft_vect_add(r.ori, ft_vect_sub(ft_vect_mult_nbr(r.dir, d.t2),
	obj->ori));
	if (ft_vect_dot(obj->axi, d.v) > 0.0)
		d.t2 = -1.0;
	return (check_solution(d.t1, d.t2));
}
