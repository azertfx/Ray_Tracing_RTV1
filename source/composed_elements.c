/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composed_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:36:08 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/09 19:03:08 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect		update_origin(t_obj *obj)
{
	t_vect res;

	res.x = obj->ori.x;
	res.y = obj->ori.y;
	res.z = obj->ori.z;
	if (obj->axi.x)
		res.x += obj->height;
	if (obj->axi.y)
		res.y += obj->height;
	if (obj->axi.z)
		res.z += obj->height;
	return (res);
}

double		pen_intersection(t_ray r, t_obj *obj)
{
	double	t_cone;
	double	t_cyl;
	t_obj	cone;

	//obj->width  = -1;
	t_cyl = cylinder_intersection(r, obj);
	if (t_cyl)
	{
		obj->width  = -1;
		return (t_cyl);
	}
	ft_memcpy(&cone, obj, sizeof(t_obj));
	cone.dsp = 0;
	cone.ori = update_origin(obj);
	cone.height = obj->height / 2;
	cone.ray = atan(obj->ray / cone.height) * (180.0 / M_PI);
	t_cone = cone_intersection(r, &cone);
	if (t_cone)
	{
		obj->width  = 2;
		return (t_cone);
	}
}
