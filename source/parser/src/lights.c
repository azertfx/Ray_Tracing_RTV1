/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:26:06 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 13:49:20 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_rt_parser(t_rt *r)
{
	r->c = 0;
	r->o = 0;
	r->l = 0;
	r->id = -1;
	r->s.amb = 100;
}

int		add_power(t_rt *r, char *v)
{
	if (r->id == LIGHT && !is_set(r->l->opt, g_pow))
	{
		if (!get_double(&(r->l->pow), v, DIST))
			return (ERROR);
		r->l->opt |= g_pow;
		return (SUCCESS);
	}
	return (ERROR);
}

int		add_angle(t_rt *r, char *v)
{
	if (r->id == LIGHT && !is_set(r->l->opt, g_ang))
	{
		if (!get_double(&(r->l->ang), v, ANGL))
			return (ERROR);
		r->l->opt |= g_ang;
		return (SUCCESS);
	}
	return (ERROR);
}

int		add_type(t_rt *r, char *v)
{
	if (r->id == LIGHT && !is_set(r->l->opt, g_lgt))
	{
		if (!ft_strcmp(v, "POINT"))
			r->l->id = POINT;
		else if (!ft_strcmp(v, "DIRECT"))
			r->l->id = DIRECT;
		else if (!ft_strcmp(v, "PARALLEL"))
			r->l->id = PARALLEL;
		else
			return (ERROR);
		r->l->opt |= g_lgt;
		return (SUCCESS);
	}
	return (ERROR);
}

int		parse_lights(t_rt *r, char **tab)
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
