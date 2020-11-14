/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:54:38 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 13:40:59 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_c(double c)
{
	if (c >= 0 && c <= 255)
		return (1);
	return (0);
}

int	get_int(int *p, char *v, int t)
{
	int i;
	int res;

	res = sscanf(v, "%d%n", p, &i);
	if (res != 1 || v[i] != '\0')
		return (ERROR);
	if (t == DIST && *p < 0)
		return (ERROR);
	if (t == ANGL && (*p < 0 || *p > 180))
		return (ERROR);
	return (SUCCESS);
}

int	get_double(double *p, char *v, int t)
{
	int i;
	int res;

	res = sscanf(v, "%lf%n", p, &i);
	if (res != 1 || v[i] != '\0' || *p < 0)
		return (ERROR);
	if (t == DIST && *p < 0)
		return (ERROR);
	if (t == ANGL && (*p < 0 || *p > 180))
		return (ERROR);
	return (SUCCESS);
}

int	get_vector(t_vect *o, char *v, int t)
{
	int i;
	int res;

	i = 0;
	res = sscanf(v, "%lf,%lf,%lf%n", &(o->x), &(o->y), &(o->z), &i);
	if (res != 3 || v[i] != '\0')
		return (ERROR);
	if (t == COLOR && !(check_c(o->x) && check_c(o->y) && check_c(o->x)))
		return (ERROR);
	if (t != ROTAT)
		return (SUCCESS);
	o->x = rad(o->x);
	o->y = rad(o->y);
	o->z = rad(o->z);
	return (SUCCESS);
}

int	free_tab(char **t, int ret)
{
	int	i;

	if (!t)
		return (ret);
	i = -1;
	while (t[++i])
		ft_memdel((void **)&t[i]);
	free(t);
	t = 0;
	return (ret);
}
