/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 02:25:27 by anabaoui          #+#    #+#             */
/*   Updated: 2020/10/17 01:02:20 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect	ft_vect_sub(t_vect u, t_vect v)
{
	t_vect vec;
	
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	vec.z = u.z - v.z;
	return (vec);
}

t_vect	ft_vect_mult_nbr(t_vect u, double t)
{
	t_vect vec;

	vec.x = u.x * t;
	vec.y = u.y * t;
	vec.z = u.z * t;
	return (vec);
}

t_vect	ft_vect_div_nbr(t_vect u, double t)
{
	t_vect vec;

	vec.x = u.x / t;
	vec.y = u.y / t;
	vec.z = u.z / t;
	return (vec);
}

t_vect	ft_vect_add(t_vect u, t_vect v)
{
	t_vect vec;

	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	vec.z = u.z + v.z;
	return (vec);
}

t_vect	ft_vect_mult(t_vect u, t_vect v)
{
	t_vect vec;

	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	vec.z = u.z * v.z;
	return (vec);
}
