/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:18:26 by hastid            #+#    #+#             */
/*   Updated: 2020/03/01 04:59:36 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_color(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, COL_SET)
			&& get_vect(&r->l->col, v, COLOR))
	{
		r->l->opt |= COL_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 5 && !IS_SET(r->o->opt, COL_SET)
			&& get_vect(&r->o->col, v, COLOR))
	{
		r->o->opt |= COL_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_axis(t_rt *r, char *v)
{
	if (r->id >= 2 && r->id <= 5 && !IS_SET(r->o->opt, AXI_SET)
			&& get_vect(&r->o->axi, v, AXIS))
	{
		r->o->opt |= AXI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_rotation(t_rt *r, char *v)
{
	if (r->id >= 2 && r->id <= 5 && !IS_SET(r->o->opt, ROT_SET)
			&& get_vect(&r->o->rot, v, ROTAT))
	{
		r->o->opt |= ROT_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_translation(t_rt *r, char *v)
{
	if (r->id >= 2 && r->id <= 5 && !IS_SET(r->o->opt, TRA_SET)
			&& get_vect(&r->o->tra, v, TRANS))
	{
		r->o->opt |= TRA_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_child(t_rt *r, char *l)
{
	int				i;
	char			**tab;
	static t_child	c_child[9] = {
		{"ray:", &add_ray},
		{"fov:", &add_fov},
		{"color:", &add_color},
		{"power:", &add_power},
		{"origin:", &add_origin},
		{"target:", &add_target},
		{"axis:", &add_axis},
		{"rotation:", &add_rotation},
		{"translation:", &add_translation},
	};

	if (!(tab = ft_strsplit(l, ' ')) || !tab[1])
		return (ERROR);
	i = -1;
	while (++i < 9)
		if (ft_strequ(tab[0], c_child[i].name))
			return (c_child[i].f(r, tab[1]));
	return (SUCCESS);
}
