/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:33:24 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/11/05 23:25:39 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		pixel_ambient(t_rt *v, int i)
{
	v->point.p_light.amb = ft_vect_div_nbr(
		ft_vect_add_nbr(v->point.p_light.amb, v->s.amb), i);
}

void		pixel_diffuse(t_rt *v, t_light *light)
{
	double	diff_pow;
	int		ce;

	ce = 0;
	diff_pow = fmax(0, ft_vect_dot(v->point.p_dir, v->point.p_normal));
	if (ce)
	{
		if (diff_pow > 0.95)
			diff_pow = 0.95;
		else if (diff_pow > 0.5)
			diff_pow = 0.5;
		else if (diff_pow > 0.25)
			diff_pow = 0.25;
		else
			diff_pow = 0.1;
	}
	v->point.p_light.def = ft_vect_add_nbr(v->point.p_light.def,
	light->pow * diff_pow);
}

void		pixel_specular(t_rt *v, t_light *light)
{
	t_vect	view_dir;
	t_vect	reflect;
	double	str;
	double	spec_pow;
	int		ce;

	ce = 0;
	view_dir = ft_vect_sub(v->c->ori, v->point.p_inter);
	ft_vect_norm(&view_dir);
	v->point.p_dir = ft_vect_mult_nbr(v->point.p_dir, -1);
	reflect = ft_vect_sub(v->point.p_dir, ft_vect_mult_nbr(
		v->point.p_normal, 2 * ft_vect_dot(
		v->point.p_normal, v->point.p_dir)));
	spec_pow = fmax(ft_vect_dot(view_dir, reflect), 0.4);
	if (ce)
	{
		if (spec_pow > 0.5)
			spec_pow = 0.9;
		else if (spec_pow > 0.25)
			spec_pow = 0.25;
		else
			spec_pow = 0.1;
	}
	str = light->pow * pow(spec_pow, 80);
	v->point.p_light.spc = ft_vect_add_nbr(v->point.p_light.spc, str);
}

double		cast_light(double min, double max, double x)
{
	if (x < min)
		return (0);
	if (x >= max)
		return (1);
	return (-2 * pow(((x - min) / (max - min)), 3)
			+ 3 * pow(((x - min) / (max - min)), 2));
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
