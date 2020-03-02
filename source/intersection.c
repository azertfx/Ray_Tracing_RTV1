/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:40:01 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/28 22:21:03 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		objects_intersection(t_ray r, t_obj *obj)
{
	double inter;

	inter = 0;
	if (obj->id == 3)
		inter = sphere_intersection(r, obj);
	else if (obj->id == 4)
		inter = cylinder_intersection(r, obj);
	else if (obj->id == 2)
		inter = plane_intersection(r, obj);
	else if (obj->id == 1)
		inter = cone_intersection(r, obj);
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
		if ((inter = objects_intersection(r, head)))
		{
			i = 1;
			if (inter <= point->inter_min)
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
	point->p_color = point->obj->col;
	if (point->obj->id == 3)
		point->p_normal = ft_vect_sub(point->p_inter, point->obj->ori);
	else if (point->obj->id == 4 || point->obj->id == 1)
	{
		point->p_normal = ft_vect_sub(point->p_inter, point->obj->ori);
		point->p_normal = ft_vect_sub(point->p_normal, ft_vect_mult_nbr(
		point->obj->axi, ft_vect_dot(point->obj->axi, point->p_normal)));
	}
	else if (point->obj->id == 2)
		point->p_normal = point->obj->axi;
	if (point->obj->id == 1)
		point->p_normal = ft_vect_add(ft_vect_mult_nbr(point->p_normal,
		cos(point->obj->ray * M_PI / 180)), ft_vect_mult_nbr(point->obj->axi,
		sin(point->obj->ray * M_PI / 180)));
	ft_vect_norm(&point->p_normal);
}
