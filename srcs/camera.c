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

void		generate_camera(t_var *v)
{
	t_vector	up;
	double		fov;

	fov = v->cam->fov * M_PI / 180;
	up = (t_vector){0, 1, 0};
	v->cam->z = ft_vector_sub(v->cam->target, v->cam->o);
	v->cam->z.z -= 0.001;
	ft_vector_norm(&v->cam->z);
	v->cam->x = ft_vector_cross(v->cam->z, up);
	ft_vector_norm(&v->cam->x);
	v->cam->y = ft_vector_cross(v->cam->x, v->cam->z);
	v->cam->height = tan(fov / 2) * 2;
	v->cam->width = v->cam->height * (IMG_W / IMG_H);
}

void		generate_camera_ray(t_var *v, t_ray *r, double y, double x)
{
	r->o = v->cam->o;
	r->dir = ft_vector_add(
		v->cam->z,
		ft_vector_add(
			ft_vector_mult_nbr(v->cam->x, (x * v->cam->width)),
			ft_vector_mult_nbr(v->cam->y, (y * v->cam->height))));
	ft_vector_norm(&r->dir);
}

t_vector	ray_trace(t_var *v, t_ray *ray, t_vector *color)
{
	if (intersection_checker(v, *ray, &v->point))
	{
		objects_normal(*ray, &v->point);
		get_pixel_color(v, color);
	}
	return (*color);
}

void		get_pixel_color(t_var *v, t_vector *light_color)
{
	t_light		*head;
	double		i;

	v->point.p_light.amb = (t_vector){0, 0, 0};
	v->point.p_light.def = (t_vector){0, 0, 0};
	v->point.p_light.spc = (t_vector){0, 0, 0};
	head = v->light;
	i = 1;
	while (head)
	{
		if (head->power)
		{
			calculate_pixel_color(v, head, i);
			i++;
		}
		head = head->next;
	}
	if (i == 1)
		v->point.p_light.amb = (t_vector){1, 1, 1};
	*light_color = ft_vector_mult(v->point.p_color, ft_vector_add(
		ft_vector_add(v->point.p_light.def, v->point.p_light.amb),
						v->point.p_light.spc));
}
