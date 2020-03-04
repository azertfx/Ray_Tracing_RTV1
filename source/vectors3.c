/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:48:53 by anabaoui          #+#    #+#             */
/*   Updated: 2020/03/04 05:26:53 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect	ft_vect_add_nbr(t_vect u, double t)
{
	t_vect vec;

	vec.x = u.x + t;
	vec.y = u.y + t;
	vec.z = u.z + t;
	return (vec);
}

t_vect	ft_vect_rotate(t_vect v, t_vect r)
{
	t_vect res;

	res.x = v.x;
	res.y = v.y * cos(r.x) + v.z * sin(r.x);
	res.z = -v.y * sin(r.x) + v.z * cos(r.x);
	v = (t_vect) {res.x, res.y, res.z};
	res.x = v.x * cos(r.y) + v.z * sin(r.y);
	res.y = v.y;
	res.z = -v.x * sin(r.y) + v.z * cos(r.y);
	v = (t_vect) {res.x, res.y, res.z};
	res.x = v.x * cos(r.z) - v.y * sin(r.z);
	res.y = v.x * sin(r.z) + v.y * cos(r.z);
	res.z = v.z;
	return (res);
}
