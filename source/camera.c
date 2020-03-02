/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:24:16 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/28 22:28:43 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		generate_camera(t_rt *v)
{
	t_vect	up;
	double		fov;

	fov = RAD(v->c->fov);
	up = (t_vect){0, 1, 0};
	v->c->z = ft_vect_sub(v->c->tar, v->c->ori);
	v->c->z.z -= 0.001;
	ft_vect_norm(&v->c->z);
	v->c->x = ft_vect_cross(v->c->z, up);
	ft_vect_norm(&v->c->x);
	v->c->y = ft_vect_cross(v->c->x, v->c->z);
	v->c->height = tan(fov / 2) * 2;
	v->c->width = v->c->height * (IMG_W / IMG_H);
}

void		generate_camera_ray(t_rt *v, t_ray *r, double y, double x)
{
	r->ori = v->c->ori;
	r->dir = ft_vect_add(
		v->c->z,
		ft_vect_add(
			ft_vect_mult_nbr(v->c->x, (x * v->c->width)),
			ft_vect_mult_nbr(v->c->y, (y * v->c->height))));
	ft_vect_norm(&r->dir);
}

t_vect	ray_trace(t_rt *v, t_ray *ray, t_vect *color)
{
	if (intersection_checker(v, *ray, &v->point))
	{
		objects_normal(*ray, &v->point);
		get_pixel_color(v, color);
	}
	return (*color);
}

void		get_pixel_color(t_rt *v, t_vect *light_color)
{
	t_light		*head;
	double		i;

	v->point.p_light.amb = (t_vect){0, 0, 0};
	v->point.p_light.def = (t_vect){0, 0, 0};
	v->point.p_light.spc = (t_vect){0, 0, 0};
	head = v->l;
	i = 1;
	while (head)
	{
		if (head->pow)
		{
			calculate_pixel_color(v, head, i);
			i++;
		}
		head = head->next;
	}
	if (i == 1)
		v->point.p_light.amb = (t_vect){1, 1, 1};
	*light_color = ft_vect_mult(v->point.p_color, ft_vect_add(
		ft_vect_add(v->point.p_light.def, v->point.p_light.amb),
						v->point.p_light.spc));
}
