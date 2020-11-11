/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_xyz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:06:26 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/09 03:29:17 by hezzahir         ###   ########.fr       */
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

double	check_up(t_vect pt_inter, t_vect lim, double t)
{
	if (is_included(pt_inter.x, lim.x))
		return (0);
	else if (is_included(pt_inter.y, lim.y))
		return (0);
	else if (is_included(pt_inter.z, lim.z))
		return (0);
	else if (is_included2(pt_inter.x, lim.x))
		return (0);
	else if (is_included2(pt_inter.y, lim.y))
		return (0);
	else if (is_included2(pt_inter.z, lim.z))
		return (0);
	return (t);
}

double	check_down(t_vect pt_inter, t_vect lim, double t)
{
	if (is_included(pt_inter.x, lim.x))
		return (t);
	else if (is_included(pt_inter.y, lim.y))
		return (t);
	else if (is_included(pt_inter.z, lim.z))
		return (t);
	else if (is_included2(pt_inter.x, lim.x))
		return (t);
	else if (is_included2(pt_inter.y, lim.y))
		return (t);
	else if (is_included2(pt_inter.z, lim.z))
		return (t);
	return (0);
}

double	ft_slice(t_ray r, t_obj *obj, double t)
{
	t_vect	pt_inter;

	pt_inter = ft_vect_add(r.ori, ft_vect_mult_nbr(r.dir, t));
	if (obj->slc)
	{
		if (obj->uod)
			return (check_up(pt_inter, obj->lim, t));
		else
			return (check_down(pt_inter, obj->lim, t));
	}
	return (t);
}
