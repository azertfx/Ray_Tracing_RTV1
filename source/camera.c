/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:24:16 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/04 01:13:34 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	generate_camera(t_rt *v)
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

void	anti_aliasing(t_rt *v, t_ray *r, double *axis, int a)
{
	static double tab[9][2] = {
		{0, 0},
		{1. / 6., -1. / 6.},
		{-1. / 6., -1. / 6.},
		{-1. / 6., 1. / 6.},
		{1. / 6., 1. / 6.},
		{1. / 3., -1. / 3.},
		{-1. / 3., -1. / 3.},
		{-1. / 3., 1. / 3.},
		{1. / 3., 1. / 3.}};

	r->dir = ft_vect_add(
			v->c->z,
			ft_vect_add(
				ft_vect_mult_nbr(v->c->x, PX_X(axis[0] + tab[a][0] + 0.5)
								* v->c->width / 2.),
				ft_vect_mult_nbr(v->c->y, PX_Y(axis[1] + tab[a][1] + 0.5)
								* v->c->height / 2.)));
}

void	motion_blur(t_ray *r, int a)
{
	static double tabi[9] = {0.956711, 0.793204, 0.655412, 0.585694,
						0.469953, 0.358863, 0.251319, 0.127367, 0.077593};

	r->time = tabi[a];
	r->ori = ft_vect_sub(r->ori, ft_vect_mult_nbr((t_vect){8, 8, 0}, r->time));
}

void	generate_camera_ray(t_rt *v, t_ray *r, double *axis, int a)
{
	int		aa;
	int		mb;

	aa = 0;
	mb = 0;
	r->ori = v->c->ori;
	r->dir = ft_vect_add(
				v->c->z,
				ft_vect_add(
					ft_vect_mult_nbr(v->c->x, PX_X(axis[0] + 0.5)
								* v->c->width / 2.),
					ft_vect_mult_nbr(v->c->y, PX_Y(axis[1] + 0.5)
								* v->c->height / 2.)));
	if (aa)
		anti_aliasing(v, r, axis, a);
	if (mb)
		motion_blur(r, a);
	ft_vect_norm(&r->dir);
}

t_vect	obj_reflection(t_vect ray_dir, t_vect p_normal)
{
	return (ft_vect_add(ray_dir, ft_vect_mult_nbr(p_normal,
			(2 * (-1 * ft_vect_dot(p_normal, ray_dir))))));
}

t_vect	obj_refraction(t_vect ray_dir, t_vect p_normal)
{
	double ior;
	double cost1;
	double cost2;

	ior = 1.0 / 1.0;
	cost1 = ft_vect_dot(p_normal, ft_vect_mult_nbr(ray_dir, -1));
	cost2 = 1 - ior * ior * (1 - cost1 * cost1);
	if (cost2 >= 0)
	{
		cost2 = sqrtf(cost2);
		if (cost1 >= 0)
			cost2 = -cost2;
		return (ft_vect_add(ft_vect_mult_nbr(ray_dir, ior),
				ft_vect_mult_nbr(p_normal, ior * cost1 + cost2)));
	}
	return (ray_dir);
}

void	check_refl_refr(t_rt *v, t_ray *ray, t_vect *depth)
{
	if (v->point.obj->rfl)
	{
		ray->dir = obj_reflection(ray->dir, v->point.p_normal);
		depth->y = v->point.obj->rfl;
		depth->z = 0;
	}
	if (v->point.obj->trs)
	{
		ray->dir = obj_refraction(ray->dir, v->point.p_normal);
		depth->z = v->point.obj->trs;
		depth->y = 0;
	}
}

t_vect	ray_trace(t_rt *v, t_ray *ray, t_vect *color, t_vect depth)
{
	if (intersection_checker(v, *ray, &v->point) && (depth.x < 4))
	{
		objects_normal(*ray, &v->point);
		apply_noise(&v->point);
		get_pixel_color(v, &v->point.p_color);
		if (depth.x != 0)
			v->point.p_color =
				ft_vect_div_nbr(v->point.p_color, depth.y ? depth.y : depth.z);
		*color = ft_vect_add(*color, v->point.p_color);
		if (v->point.obj->rfl || v->point.obj->trs)
		{
			check_refl_refr(v, ray, &depth);
			depth.x++;
			ft_vect_norm(&ray->dir);
			ray->ori = ft_vect_add(v->point.p_inter,
						ft_vect_mult_nbr(ray->dir, 0.5));
			ray_trace(v, ray, color, depth);
		}
	}
	return (*color);
}

void	get_pixel_color(t_rt *v, t_vect *light_color)
{
	t_light *head;
	double	i;

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
	*light_color = ft_vect_mult(v->point.p_color,
					ft_vect_add(ft_vect_add(v->point.p_light.def,
								v->point.p_light.amb), v->point.p_light.spc));
}
