/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:40:01 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/14 01:01:05 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		objects_intersection(t_ray r, t_obj *obj, t_rt *rt)
{
	double	inter;

	inter = 0;
	if (obj->id == CONE)
		inter = cone_intersection(r, obj);
	else if (obj->id == PLA)
		inter = plane_intersection(r, obj);
	else if (obj->id == SPH)
		inter = sphere_intersection(r, obj);
	else if (obj->id == CYL)
		inter = cylinder_intersection(r, obj);
	else if (obj->id == PARA)
		inter = paraboloid_intersection(r, obj);
	else if (obj->id == DISC)
		inter = disc_intersection(r, obj);
	else if (obj->id == SQUAR)
		inter = square_intersection(r, obj);
	else if (obj->id == HEMIS)
		inter = hemisphere_intersection(r, obj);
	else if (obj->id == PEN)
		inter = pen_intersection(r, obj);
	else
		return (0);
	return (negative_objects(inter, r, obj->t_max, rt));
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
			if (inter < point->inter_min)
			{
				point->inter_min = inter;
				point->obj = head;
			}
		}
		head = head->next;
	}
	return (i);
}

int			check_condition(int id)
{
	if (id == 2 || id == 5 || id == 9 || id == PEN)
		return (1);
	return (0);
}

void		objects_normal(t_ray r, t_point *p)
{
	p->p_inter = ft_vect_add(r.ori,
				ft_vect_mult_nbr(r.dir, p->inter_min));
	if (p->obj->txt.t)
		color_texture(p);
	else
		p->p_color = p->obj->col;
	if (p->obj->id == SPH)
		p->p_normal = ft_vect_sub(p->p_inter, p->obj->ori);
	else if (check_condition(p->obj->id))
	{
		p->p_normal = ft_vect_sub(p->p_inter, p->obj->ori);
		p->p_normal = ft_vect_sub(p->p_normal, ft_vect_mult_nbr(p->obj->axi,
			ft_vect_dot(p->obj->axi, p->p_normal)));
	}
	else if (p->obj->id == 3 || p->obj->id == 7 || p->obj->id == 8)
		p->p_normal = p->obj->axi;
	if (p->obj->id == CONE || p->obj->id == PEN)
		p->p_normal = ft_vect_add(ft_vect_mult_nbr(p->p_normal,
		cos(RAD(p->obj->ray))), ft_vect_mult_nbr(p->obj->axi,
		sin(RAD(p->obj->ray))));
	if (p->obj->id == PARA)
		p->p_normal = ft_vect_sub(ft_vect_sub(p->p_inter, p->obj->ori),
		ft_vect_mult_nbr(p->obj->axi, ft_vect_dot(ft_vect_sub(p->p_inter,
		p->obj->ori), p->obj->axi) + p->obj->ray));
	ft_vect_norm(&p->p_normal);
}
