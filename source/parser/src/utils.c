/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:54:38 by hastid            #+#    #+#             */
/*   Updated: 2020/10/17 00:16:41 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	if (t == COLOR && !(V_COLOR(o->x) && V_COLOR(o->y) && V_COLOR(o->x)))
		return (ERROR);
	if (t != ROTAT)
		return (SUCCESS);
	o->x = RAD(o->x);
	o->y = RAD(o->y);
	o->z = RAD(o->z);
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
