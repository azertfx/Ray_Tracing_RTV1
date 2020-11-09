/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:00:37 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/09 02:15:00 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	exit_err(t_rt *r)
{
	free_rt(r);
	ft_putstr_fd("ERROR\n", 2);
	exit(1);
	return (ERROR);
}

double	check_solution(double t1, double t2)
{
	double	t;

	t = 0;
	if (t1 < 0.0)
		t1 = t2;
	if (t2 < 0.0)
		t2 = t1;
	t = fmax(t1, t2);
	if (t > MIN_NBR)
		return (t);
	return (0);
}

double	equation_solve(t_ray ray, t_delt d, t_obj *obj)
{
	double	delta;
	double	inter1;
	double	inter2;

	delta = d.b * d.b - 4 * d.a * d.c;
	if (delta < 0 || d.a == 0)
		return (0);
	inter1 = (-d.b - sqrt(delta)) / (2 * d.a);
	inter2 = (-d.b + sqrt(delta)) / (2 * d.a);
	if ((inter2 < MIN_NBR && inter1 < MIN_NBR))
		return (0);
	if ((inter1 <= inter2 && inter1 > MIN_NBR)
								|| (inter2 < inter1 && inter2 > MIN_NBR))
	{
		obj->t_max = fmax(inter1, inter2);
		return (ft_slice(ray, obj, fmin(inter1, inter2)));
	}
	return (0);
}
