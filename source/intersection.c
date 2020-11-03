/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:40:01 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/03 00:54:33 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double      solve_equation_neg(t_delt d, double t_min, double t_max)
{
    double	t1;
	double	t2;
	double	delta;

	delta = d.b * d.b - 4 * d.a * d.c;
	if (delta <= 0 || d.a == 0)
		return (t_min);
	t1 = (-d.b - sqrt(delta)) / (2 * d.a);
	t2 = (-d.b + sqrt(delta)) / (2 * d.a);
	if (t1 < MIN_NBR || t2 < MIN_NBR)
		return (t_min);
    if ((t_min > t1 && t_min < t2) || (t_min > t2 && t_min < t1))
		return ((t1 < t_max && t2 < t_max) ? t_max : 0);
    return (t_min);
}

double		intersect_cone_neg(t_ray r, t_obj *obj, double t_min, double t_max)
{

	t_delt d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	ft_vect_norm(&obj->axi);
	d.a = ft_vect_dot(r.dir, r.dir) - (1 + pow(tan(RAD(obj->ray)), 2)) *
										pow(ft_vect_dot(r.dir, obj->axi), 2);
	d.b = 2 * (ft_vect_dot(r.dir, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2)) *
		ft_vect_dot(r.dir, obj->axi) * ft_vect_dot(obj_center, obj->axi));
	d.c = ft_vect_dot(obj_center, obj_center) - (1 + pow(tan(RAD(obj->ray)), 2)) *
								pow(ft_vect_dot(obj_center, obj->axi), 2);
	return (solve_equation_neg(d, t_min, t_max));
}

double		intersect_sphere_neg(t_ray r, t_obj *obj, double t_min, double t_max)
{
	t_delt d;
	t_vect	obj_center;

	obj_center = ft_vect_sub(r.ori, obj->ori);
	d.a = ft_vect_dot(r.dir, r.dir);
	d.b = 2 * ft_vect_dot(r.dir, obj_center);
	d.c = ft_vect_dot(obj_center, obj_center) - obj->ray * obj->ray;
	return (solve_equation_neg(d, t_min, t_max));
}

double		intersect_cylinder_neg(t_ray r, t_obj *obj, double t_min, double t_max)
{
	t_delt d;
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
	return ((solve_equation_neg(d, t_min, t_max)));
}

double		negative_objects(double t_min, t_ray r, double t_max, t_rt *rt)
{
	int		i;
	double	dist;
    t_obj   *obj;

	i = 0;
    obj = rt->o;
	if (!(dist = t_min))
		return (0);
	while (obj)
	{
		if (obj->neg)
		{
			// printf("%d", obj->neg);
            if (obj->id == CONE)
				dist = intersect_cone_neg(r, obj, t_min, t_max);
			else if (obj->id == SPHERE)
				dist = intersect_sphere_neg(r, obj, t_min, t_max);
			else if (obj->id == CYLINDER)
				dist = intersect_cylinder_neg(r, obj, t_min, t_max);
			// else if (obj->id == PARABOL)
			// 	dist = intersect_paraboloid_neg(r, obj, t_min, t_max);
		}
        obj = obj->next;
	}
	return (dist);
}

double		objects_intersection(t_ray r, t_obj *obj, t_rt *rt)
{
	double inter;

	inter = 0;
	if (obj->id == SPHERE)
		inter = negative_objects(sphere_intersection(r, obj), r, obj->t_max, rt);
	else if (obj->id == CYLINDER)
		inter = negative_objects(cylinder_intersection(r, obj), r, obj->t_max, rt);
	else if (obj->id == PLANE)
		inter = negative_objects(plane_intersection(r, obj), r, obj->t_max, rt);
	else if (obj->id == CONE)
		inter = negative_objects(cone_intersection(r, obj), r, obj->t_max, rt);
	return (inter);
}

double		intersection_checker(t_rt *v, t_ray r, t_point *point)
{
	t_obj	*head;
	double	inter;
	double	i;

	head = v->o;
	i = 0;
	point->inter_min = MAX_NBR;
	while (head)
	{
		if (!(head->neg) && (inter = objects_intersection(r, head, v)))
		{
			i = 1;
			if (inter <= point->inter_min )
			{
				point->inter_min = inter;
				point->obj = head;
			}
		}
		head = head->next;
	}
	return (i);
}

void		objects_normal(t_ray r, t_point *point)
{
	point->p_inter = ft_vect_add(r.ori,
				ft_vect_mult_nbr(r.dir, point->inter_min));
	if (point->obj->txt.t)
		getColorFromTexture(point);
	else
		point->p_color = point->obj->col;
	if (point->obj->id == SPHERE)
		point->p_normal = ft_vect_sub(point->p_inter, point->obj->ori);
	else if (point->obj->id == CONE || point->obj->id == CYLINDER)
	{
		point->p_normal = ft_vect_sub(point->p_inter, point->obj->ori);
		point->p_normal = ft_vect_sub(point->p_normal, ft_vect_mult_nbr(
		point->obj->axi, ft_vect_dot(point->obj->axi, point->p_normal)));
	}
	else if (point->obj->id == PLANE)
		point->p_normal = point->obj->axi;
	if (point->obj->id == CONE)
		point->p_normal = ft_vect_add(ft_vect_mult_nbr(point->p_normal,
		cos(RAD(point->obj->ray))), ft_vect_mult_nbr(point->obj->axi,
		sin(RAD(point->obj->ray))));
	ft_vect_norm(&point->p_normal);
}
