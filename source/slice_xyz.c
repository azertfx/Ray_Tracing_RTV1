/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_xyz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:06:26 by hezzahir          #+#    #+#             */
/*   Updated: 2020/10/22 19:06:28 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void show_vect(t_vect v)
// {
// 	printf("|%lf %lf %lf|\n",v.x,v.y,v.z);
// }

int is_included(double a, double b)
{
	if (a > 0 && b > 0 && a > b)
		return (1);
	return (0);
}

double ft_slice(t_ray r, double t)
{
	/*
	** Waiting for @Hamza_Astid to add those on ft_obj struct:
	**						+ the slice(ON/OFF) == (1 / 0)
	** 						+ the up_down (up = 1 && down = 0)
	**						+ the vector of limition / Slicing
	*/
	int slice = 1;			// slice YES or NO // obj->slice = 0 means no slice either = 1
	int up_down = 0;		// slice from the up or down
	t_vect lim = {0, 0, 0}; // the vector of limiting
	t_vect pt_inter = ft_vect_add(r.ori, ft_vect_mult_nbr(r.dir, t));
	//show_vect(pt_inter);
	if (slice)
	{
		if (up_down)
		{
			if (is_included(pt_inter.x, lim.x))
				return (0);
			else if (is_included(pt_inter.y, lim.y))
				return (0);
			else if (is_included(pt_inter.z, lim.z))
				return (0);
		}

		/*if (pt_inter.x > lim.x)
				return (0);*/
		/*if (!up_down)
			if (pt_inter.x < lim.x || pt_inter.y < lim.y || pt_inter.z < lim.z)
				return (0);*/
	}
	//r.dir.x = r.dir.x;
	return (t);
}
