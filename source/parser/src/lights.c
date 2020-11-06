/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:26:06 by hastid            #+#    #+#             */
/*   Updated: 2020/11/06 02:51:01 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_power(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, POW_SET))
	{
		if (!get_double(&(r->l->pow), v, DIST))
			return (ERROR);
		r->l->opt |= POW_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_angle(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, ANG_SET))
	{
		if (!get_double(&(r->l->ang), v, ANGL))
			return (ERROR);
		r->l->opt |= ANG_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_type(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, LIGHT_T))
	{
		if (!ft_strcmp(v, "POINT"))
			r->l->id = POINT;
		else if (!ft_strcmp(v, "DIRECT"))
			r->l->id = DIRECT;
		else if (!ft_strcmp(v, "PARALLEL"))
			r->l->id = PARALLEL;
		else
			return (ERROR);
		r->l->opt |= LIGHT_T;
		return (SUCCESS);
	}
	return (ERROR);
}

int	parse_lights(t_rt *r, char **tab)
{
	int				i;
	int				ret;
	static t_child	c_child[6] = {
		{"type:", &add_type},
		{"axis:", &add_axis},
		{"angle:", &add_angle},
		{"color:", &add_color},
		{"power:", &add_power},
		{"origin:", &add_origin},
	};

	ret = ERROR;
	i = -1;
	while (++i < 6)
		if (ft_strequ(tab[0], c_child[i].name))
			break ;
	if (i < 6 && ft_strequ(tab[0], c_child[i].name))
		ret = c_child[i].f(r, tab[1]);
	return (free_tab(tab, ret));
}
