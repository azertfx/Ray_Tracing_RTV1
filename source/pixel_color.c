/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:12:38 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/03 01:18:49 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		shadow_checker(t_rt *v, t_light *light)
{
	t_point		point;
	t_ray		r;
	double		dist_light;
	double		dist_object;

	r.ori = ft_vect_add(v->point.p_inter,
			(ft_vect_mult_nbr(v->point.p_normal, 0.5)));
	r.dir = ft_vect_sub(light->ori, r.ori);
	ft_vect_norm(&r.dir);
	if (intersection_checker(v, r, &point))
	{
		// if (point.obj->id == SPHERE)
		// 	return (0);
		objects_normal(r, &point);
		dist_light = ft_vect_dist(v->point.p_inter, light->ori);
		dist_object = ft_vect_dist(v->point.p_inter, point.p_inter);
		if (dist_object < dist_light)
		{
			if (point.obj->trs)
				return (point.obj->trs + 1);
			return (1);
		}
	}
	return (0);
}

void		pixel_ambient(t_rt *v, int i)
{
	v->point.p_light.amb = ft_vect_div_nbr(
		ft_vect_add_nbr(v->point.p_light.amb, 100), i);
}

void		pixel_diffuse(t_rt *v, t_light *light)
{
	v->point.p_light.def = ft_vect_add_nbr(v->point.p_light.def,
	light->pow * fmax(0, ft_vect_dot(v->point.p_dir, v->point.p_normal)));
}

void		pixel_specular(t_rt *v, t_light *light)
{
	t_vect	view_dir;
	t_vect	reflect;
	double	str;

	view_dir = ft_vect_sub(v->c->ori, v->point.p_inter);
	ft_vect_norm(&view_dir);
	v->point.p_dir = ft_vect_mult_nbr(v->point.p_dir, -1);
	reflect = ft_vect_sub(v->point.p_dir, ft_vect_mult_nbr(
		v->point.p_normal, 2 * ft_vect_dot(
		v->point.p_normal, v->point.p_dir)));
	str = light->pow * pow(fmax(ft_vect_dot(view_dir, reflect), 0.4), 80);
	v->point.p_light.spc = ft_vect_add_nbr(v->point.p_light.spc, str);
}

double		cast_light(double min, double max, double x)
{
	if (x < min)
		return (0);
	if (x >= max)
		return (1);
	return (-2 * pow(((x - min) / (max - min)), 3) + 3 * pow(((x - min) / (max - min)), 2));
}

double		spotlight(t_vect p, t_light light, double cos_angle)
{
	t_vect		v;
	double		cos_in;
	double		cos_out;
	double		cos_direction;

	v = ft_vect_sub(p, light.ori);
	ft_vect_norm(&v);
	cos_in = fabs(cos(RAD(cos_angle)));
	cos_out = cos_in - 0.07;
	cos_direction = ft_vect_dot(v, light.axi);
	return (cast_light(cos_out, cos_in, cos_direction));
}

void		calculate_pixel_color(t_rt *v, t_light *light, int i)
{
	double dir;
	int shadow;

	dir = 1.0;
	shadow = shadow_checker(v, light);
	pixel_ambient(v, i);
	if (light->id == DIRECT && !(dir = spotlight(v->point.p_inter, *light, light->ang)))
		return ;
	if (!shadow || shadow > 1)
	{
		v->point.p_dir = ft_vect_sub(light->ori, v->point.p_inter);
		ft_vect_norm(&v->point.p_dir);
		pixel_diffuse(v, light);
		v->point.p_light.def = ft_vect_mult_nbr(v->point.p_light.def, dir);
		pixel_specular(v, light);
		if (shadow > 1)
		{
			shadow--;
			v->point.p_light.def = ft_vect_div_nbr(v->point.p_light.def, shadow);
			v->point.p_light.spc = ft_vect_div_nbr(v->point.p_light.spc, shadow);
		}
	}
}
