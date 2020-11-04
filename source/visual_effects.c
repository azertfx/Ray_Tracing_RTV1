/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:27:25 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/11/04 01:29:09 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
