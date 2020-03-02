/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 02:26:28 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/23 13:50:16 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect	ft_vect_cross(t_vect u, t_vect v)
{
	t_vect vec;

	vec.x = u.y * v.z - u.z * v.y;
	vec.y = u.z * v.x - u.x * v.z;
	vec.z = u.x * v.y - u.y * v.x;
	return (vec);
}

t_vect	ft_vect_norm(t_vect *vec)
{
	double	w;

	w = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (w)
	{
		vec->x /= w;
		vec->y /= w;
		vec->z /= w;
	}
	else
		*vec = (t_vect){0, 0, 0};
	return (*vec);
}

double		ft_vect_dot(t_vect u, t_vect v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double		ft_vect_length(t_vect vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double		ft_vect_dist(t_vect u, t_vect v)
{
	return ((u.x - v.x) * (u.x - v.x) +
			(u.y - v.y) * (u.y - v.y) +
			(u.z - v.z) * (u.z - v.z));
}
