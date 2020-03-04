/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:12:38 by anabaoui          #+#    #+#             */
/*   Updated: 2020/03/04 13:44:14 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	shadow_checker(t_rt *v, t_light *light)
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
			return (1);
	}
	return (0);
}

void	pixel_ambient(t_rt *v, int i)
{
	v->point.p_light.amb = ft_vect_div_nbr(
		ft_vect_add_nbr(v->point.p_light.amb, 80), i);
}

void	pixel_diffuse(t_rt *v, t_light *light)
{
	v->point.p_light.def = ft_vect_add_nbr(v->point.p_light.def,
	light->pow * fmax(0, ft_vect_dot(v->point.p_dir, v->point.p_normal)));
}

void	pixel_specular(t_rt *v, t_light *light)
{
	t_vect	view_dir;
	t_vect	reflect;
	double		str;

	view_dir = ft_vect_sub(v->c->ori, v->point.p_inter);
	ft_vect_norm(&view_dir);
	v->point.p_dir = ft_vect_mult_nbr(v->point.p_dir, -1);
	reflect = ft_vect_sub(v->point.p_dir, ft_vect_mult_nbr(
		v->point.p_normal, 2 * ft_vect_dot(
		v->point.p_normal, v->point.p_dir)));
	str = light->pow * pow(fmax(ft_vect_dot(view_dir, reflect), 0.4), 100);
	v->point.p_light.spc = ft_vect_add_nbr(v->point.p_light.spc, str);
}

void	calculate_pixel_color(t_rt *v, t_light *light, int i)
{
	pixel_ambient(v, i);
	if (!shadow_checker(v, light))
	{
		v->point.p_dir = ft_vect_sub(light->ori, v->point.p_inter);
		ft_vect_norm(&v->point.p_dir);
		pixel_diffuse(v, light);
		pixel_specular(v, light);
	}
}
