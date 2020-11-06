/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:12:38 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/06 01:50:59 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_pixel_color(t_rt *v, int i, int j, t_vect color)
{
	filters(&color, 53);
	v->m.img_data[(j * IMG_W + i) * 4 + 0] = color.z;
	v->m.img_data[(j * IMG_W + i) * 4 + 1] = color.y;
	v->m.img_data[(j * IMG_W + i) * 4 + 2] = color.x;
	v->m.img_data[(j * IMG_W + i) * 4 + 3] = 0;
}

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

void	calculate_pixel_color(t_rt *v, t_light *light, int i)
{
	double	dir;
	int		shadow;

	dir = 1.0;
	shadow = shadow_checker(v, light);
	pixel_ambient(v, i);
	if (light->id == DIRECT &&
		!(dir = spotlight(v->point.p_inter, *light, light->ang)))
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
			v->point.p_light.def =
				ft_vect_div_nbr(v->point.p_light.def, shadow);
			v->point.p_light.spc =
				ft_vect_div_nbr(v->point.p_light.spc, shadow);
		}
	}
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
