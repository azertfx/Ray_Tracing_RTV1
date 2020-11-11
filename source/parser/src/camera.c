/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:23:30 by hastid            #+#    #+#             */
/*   Updated: 2020/11/06 02:32:28 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_fov(t_rt *r, char *v)
{
	if (r->id == CAMERA && !IS_SET(r->c->opt, FOV_SET))
	{
		if (get_double(&(r->c->fov), v, ANGL) == ERROR)
			return (ERROR);
		r->c->opt |= FOV_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_target(t_rt *r, char *v)
{
	if (r->id == CAMERA && !IS_SET(r->c->opt, TAR_SET))
	{
		if (get_vector(&r->c->tar, v, NONE) == ERROR)
			return (ERROR);
		r->c->opt |= TAR_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	parse_camera(t_rt *r, char **tab)
{
	int				i;
	int				ret;
	static t_child	c_child[4] = {
		{"fov:", &add_fov},
		{"origin:", &add_origin},
		{"target:", &add_target},
	};

	ret = ERROR;
	i = -1;
	while (++i < 4)
		if (ft_strequ(tab[0], c_child[i].name))
			break ;
	if (i < 4 && ft_strequ(tab[0], c_child[i].name))
		ret = c_child[i].f(r, tab[1]);
	return (free_tab(tab, ret));
}
