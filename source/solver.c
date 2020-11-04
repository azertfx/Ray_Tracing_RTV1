/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:00:37 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/04 01:33:20 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		check_solution(double t1, double t2)
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

double		equation_solve(t_ray ray, double a, double b, double c, t_obj *obj)
{
	double	delta;
	double	inter1;
	double	inter2;

	delta = b * b - 4 * a * c;
	if (delta < 0 || a == 0)
		return (0);
	inter1 = (-b - sqrt(delta)) / (2 * a);
	inter2 = (-b + sqrt(delta)) / (2 * a);
	if ((inter2 < MIN_NBR && inter1 < MIN_NBR))
		return (0);
	if ((inter1 < inter2 && inter1 > MIN_NBR)
								|| (inter2 < inter1 && inter2 > MIN_NBR))
	{
		obj->t_max = fmax(inter1, inter2);
		return (ft_slice(ray, fmin(inter1, inter2)));
	}
	return (0);
}
