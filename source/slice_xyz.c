/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_xyz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:06:26 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/04 04:33:37 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_included(double a, double b)
{
	if (a > 0 && b > 0 && a > b)
		return (1);
	return (0);
}
int		is_included2(double a, double b)
{
	if (a < 0 && b < 0 && a < b)
		return (1);
	return (0);
}

double	ft_slice(t_ray r, t_obj *obj, double t)
{
	t_vect pt_inter;

	pt_inter = ft_vect_add(r.ori, ft_vect_mult_nbr(r.dir, t));
	if (obj->slc)
	{
		if (obj->uod)
		{
			if (is_included(pt_inter.x, obj->lim.x))
				return (0);
			else if (is_included(pt_inter.y, obj->lim.y))
				return (0);
			else if (is_included(pt_inter.z, obj->lim.z))
				return (0);
			else if (is_included2(pt_inter.x, obj->lim.x))
				return (0);
			else if (is_included2(pt_inter.y, obj->lim.y))
				return (0);
			else if (is_included2(pt_inter.z, obj->lim.z))
				return (0);
		}
		else
		{
/*
** To DO : make it for up_down == 0
*/
		}
	}
	return (t);
}
