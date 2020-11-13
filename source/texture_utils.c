/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:26:12 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 12:14:46 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	angle_plan(t_obj *plane_temp, t_vect p)
{
	plane_temp->txt.um = p.x * 0.01;
	plane_temp->txt.vm = p.y * 0.01;
	plane_temp->txt.um -= floor(plane_temp->txt.um);
	plane_temp->txt.vm -= floor(plane_temp->txt.vm);
}

void	angle_cone(t_obj *cone_temp, t_vect p)
{
	cone_temp->txt.um = (atan2(p.x, p.z) / (2.0 * M_PI));
	cone_temp->txt.vm = (p.y + 5.0 / 2) / 5.0;
	cone_temp->txt.um -= floor(cone_temp->txt.um);
	cone_temp->txt.vm -= floor(cone_temp->txt.vm);
}

void	angle_sphere(t_obj *sphere_temp, t_vect p)
{
	double phi;
	double theta;

	phi = atan2(p.z, p.x);
	theta = asin(p.y / sphere_temp->ray);
	sphere_temp->txt.um = 1 - (phi + M_PI) / (2.0 * M_PI);
	sphere_temp->txt.vm = (theta + M_PI / 2.0) / M_PI;
}

void	angle_cylinder(t_obj *plane_temp, t_vect p)
{
	plane_temp->txt.um = (atan2(p.x, p.z) / (2.0 * M_PI));
	plane_temp->txt.vm = (p.y + 4.0 / 2) / 4.0;
	plane_temp->txt.um -= floor(plane_temp->txt.um);
	plane_temp->txt.vm -= floor(plane_temp->txt.vm);
}

void	get_angle(t_obj *obj, t_vect inter)
{
	if (obj->id == PLA)
		angle_plan(obj, inter);
	else if (obj->id == CONE)
		angle_cone(obj, inter);
	else if (obj->id == SPH)
		angle_sphere(obj, inter);
	else if (obj->id == CYL)
		angle_cylinder(obj, inter);
}
