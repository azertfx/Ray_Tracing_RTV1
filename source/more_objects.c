/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 01:00:56 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/04 01:06:19 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

double		disc_intersection(t_ray r, t_obj *obj)
{
	t_inter		i;
	t_delt		d;

	i.obj_center = ft_vect_sub(obj->ori, r.ori);
	if ((i.nor_dir = ft_vect_dot(r.dir, obj->axi)))
		i.inter = ft_vect_dot(i.obj_center, obj->axi) / i.nor_dir;
	else
		return (0);
	if (i.inter < MIN_NBR || i.inter > MAX_NBR)
		return (0);
	i.pt = ft_vect_add(r.ori, ft_vect_mult_nbr(r.dir, i.inter));
	d.v = ft_vect_sub(obj->ori, i.pt);
	d.t = ft_vect_dot(d.v, d.v);
	if (sqrtf(d.t) <= obj->ray)
		return (i.inter + MIN_NBR);
	else
		return (0);
}

double		square_intersection(t_ray r, t_obj *obj)
{
	t_inter s;

	s.obj_center = ft_vect_sub(obj->ori, r.ori);
	if ((s.nor_dir = ft_vect_dot(r.dir, obj->axi)))
		s.inter = ft_vect_dot(s.obj_center, obj->axi) / s.nor_dir;
	else
		return (0);
	if (s.inter < MIN_NBR || s.inter > MAX_NBR)
		return (0);
	s.pt = ft_vect_add(r.ori, ft_vect_mult_nbr(r.dir, s.inter));
	s.pt = ft_vect_sub(s.pt, obj->ori);
	t_vect e1 = {7,0,0};
	t_vect e2 = {0,-7,0};
	s.width = ft_vect_length(e1);
	s.height = ft_vect_length(e2);
	s.proj1 = ft_vect_dot(s.pt, e1) / s.width;
	s.proj2 = ft_vect_dot(s.pt, e2) / s.height;
	if ((s.proj1 < s.width && s.proj1 > 0) &&
					(s.proj2 < s.height && s.proj2 > 0))
		return (s.inter + MIN_NBR);
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
