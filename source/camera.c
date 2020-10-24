/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:24:16 by anabaoui          #+#    #+#             */
/*   Updated: 2020/10/21 20:41:54 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void generate_camera(t_rt *v)
{
	t_vect up;
	double fov;

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

void generate_camera_ray(t_rt *v, t_ray *r, double y, double x)
{
	r->ori = v->c->ori;
	r->dir = ft_vect_add(
		v->c->z,
		ft_vect_add(
			ft_vect_mult_nbr(v->c->x, x * v->c->width / 2.),
			ft_vect_mult_nbr(v->c->y, y * v->c->height / 2.)));
	ft_vect_norm(&r->dir);
}

t_vect obj_reflection(t_vect ray_dir, t_vect p_normal)
{
	return ft_vect_add(ray_dir, ft_vect_mult_nbr(p_normal, (2 * (-1 * ft_vect_dot(p_normal, ray_dir)))));
}

t_vect obj_refraction(t_vect ray_dir, t_vect p_normal)
{
	double ior = 1.0 / 1.0;
	double cost1 = ft_vect_dot(p_normal, ft_vect_mult_nbr(ray_dir, -1));
	double cost2 = 1 - ior * ior * (1 - cost1 * cost1);
	if (cost2 >= 0)
	{
		cost2 = sqrtf(cost2);
		if (cost1 >= 0)
			cost2 = -cost2;
		return ft_vect_add(ft_vect_mult_nbr(ray_dir, ior), ft_vect_mult_nbr(p_normal, ior * cost1 + cost2));
	}
	return (ray_dir);
}

t_vect ray_trace(t_rt *v, t_ray *ray, t_vect *color, t_vect depth)
{
	if (intersection_checker(v, *ray, &v->point) && (depth.x < 4))
	{
		objects_normal(*ray, &v->point);
		get_pixel_color(v, &v->point.p_color);
		if (depth.x != 0)
			v->point.p_color = ft_vect_div_nbr(v->point.p_color, depth.y ? depth.y : depth.z);
		*color = ft_vect_add(*color, v->point.p_color);
		if (v->point.obj->rfl || v->point.obj->trs)
		{
			if (v->point.obj->rfl)
			{
				ray->dir = obj_reflection(ray->dir, v->point.p_normal);
				depth.y = v->point.obj->rfl;
				depth.z = 0;
			}
			if (v->point.obj->trs)
			{
				ray->dir = obj_refraction(ray->dir, v->point.p_normal);
				depth.z = v->point.obj->trs;
				depth.y = 0;
			}
			depth.x++;
			ft_vect_norm(&ray->dir);
			ray->ori = ft_vect_add(v->point.p_inter, ft_vect_mult_nbr(ray->dir, 0.5));
			ray_trace(v, ray, color, depth);
		}
	}
	return (*color);
}

void get_pixel_color(t_rt *v, t_vect *light_color)
{
	t_light *head;
	double i;

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

	*light_color = ft_vect_mult(v->point.p_color, ft_vect_add(
													  ft_vect_add(v->point.p_light.def, v->point.p_light.amb),
													  v->point.p_light.spc));
}
