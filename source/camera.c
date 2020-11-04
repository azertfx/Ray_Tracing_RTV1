/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:24:16 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/04 04:07:24 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	generate_camera(t_rt *v)
{
	t_vect up;
	double fov;

	v->c->ori.z += v->event.move_z;
	v->c->ori.x += v->event.move_x;
	v->c->tar.y += v->event.rot_y;
	v->c->tar.x += v->event.rot_x;
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
