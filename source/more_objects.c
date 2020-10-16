/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 01:00:56 by hezzahir          #+#    #+#             */
/*   Updated: 2020/03/13 19:22:51 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

double	Disc_intersection(t_ray r, t_obj *obj)
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
	t_vect v = ft_vect_sub(obj->ori, p);
	double distance = ft_vect_dot(v,v);
	if (sqrtf(distance) <= obj->ray)
		return (inter + MIN_NBR);
	else
		return (0);
}

double	square_intersection(t_ray r, t_obj *obj)
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

double	limited_cone_intersection(t_ray r, t_obj *obj)
{
	double		a;
	double		b;
	double		c;
	double		m;
	double		t;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	a = ft_vect_dot(r.dir, r.dir) - (1 + pow(tan(RAD(obj->ray)), 2)) *
										pow(ft_vect_dot(r.dir, obj->axi), 2);
	b = 2 * (ft_vect_dot(r.dir, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2)) *
		ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi));
	c = ft_vect_dot(obj_center, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2)) *
								pow(ft_vect_dot(obj_center, obj->axi), 2);
	t = equation_solve(a, b, c);
	if(t)
	{
		m = ft_vect_dot(r.dir, obj->axi) * t + ft_vect_dot(obj_center, obj->axi);
		if (m <= 0 && m >= -30)
			return (t);
	}
	return (0);
}

double	limited_cylinder_intersection(t_ray r, t_obj *obj)
{
	double		a;
	double		b;
	double		c;
	double		t;
	double		m;
	t_vect		obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	a = ft_vect_dot(r.dir, r.dir) - ft_vect_dot(r.dir, obj->axi) *
												ft_vect_dot(r.dir, obj->axi);
	b = 2 * (ft_vect_dot(r.dir, obj_center) -
	(ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi)));
	c = ft_vect_dot(obj_center, obj_center) -
			ft_vect_dot(obj_center, obj->axi) *
						ft_vect_dot(obj_center, obj->axi) - obj->ray * obj->ray;
	t = equation_solve(a, b, c);
	if(t)
	{
		m = ft_vect_dot(r.dir, obj->axi) * t + ft_vect_dot(obj_center, obj->axi);
		if (m <= 30 && m >= -30)
			return (t);
	}
	return (0);
}


double	hemisphere_intersection(t_ray r, t_obj *obj)
{
	double		a;
	double		b;
	double		c;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	a = ft_vect_dot(r.dir, r.dir);
	b = 2 * ft_vect_dot(r.dir, obj_center);
	c = ft_vect_dot(obj_center, obj_center) - obj->ray * obj->ray;
	double	delta;
	double	t1;
	double	t2;

	delta = b * b - 4 * a * c;
	if (delta < 0) return (0);
	t1 = (-b - sqrt(delta)) / (2 * a);
	t2 = (-b + sqrt(delta)) / (2 * a);
	t_vect v = ft_vect_add(r.ori, ft_vect_sub(ft_vect_mult_nbr(r.dir,t1),
	obj->ori));
	if (ft_vect_dot(obj->axi, v) > 0.0)
		t1 = -1.0;
	v = ft_vect_add(r.ori, ft_vect_sub(ft_vect_mult_nbr(r.dir,t2),
	obj->ori));
	if (ft_vect_dot(obj->axi, v) > 0.0)
		t2 = -1.0;
	double	t;
	if (t1 < 0.0)
		t1 = t2;
	if (t2 < 0.0)
		t2 = t1;
	t = fmax(t1, t2);
	if (t > MIN_NBR)
		return (t);
	return (0);
}
