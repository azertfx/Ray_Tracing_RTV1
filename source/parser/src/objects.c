/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:20:15 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 09:46:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_disruption(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, DSP_SET))
	{
		if (get_int(&(r->o->dsp), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= DSP_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_limvect1(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, LM1_SET))
	{
		if (get_vector(&r->o->e1, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= LM1_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_limvect2(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, LM2_SET))
	{
		if (get_vector(&r->o->e2, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= LM2_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_textures(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, TXT_SET))
	{
		if (get_int(&(r->o->txt.t), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= TXT_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

static t_child	g_child[18] = {
	{"ray:", &add_ray},
	{"axis:", &add_axis},
	{"color:", &add_color},
	{"width:", &add_width},
	{"height:", &add_height},
	{"origin:", &add_origin},
	{"negative:", &add_negative},
	{"rotation:", &add_rotation},
	{"reflection:", &add_reflection},
	{"translation:", &add_translation},
	{"transparence:", &add_transparence},
	{"slice:", &add_slice},
	{"upOrDown:", &add_upordown},
	{"limit:", &add_limit},
	{"disruption:", &add_disruption},
	{"e1:", &add_limvect1},
	{"e2:", &add_limvect2},
	{"texture:", &add_textures},
};

int	parse_objects(t_rt *r, char **tab)
{
	int				i;
	int				ret;

	ret = ERROR;
	i = -1;
	while (++i < 18)
		if (ft_strequ(tab[0], g_child[i].name))
			break ;
	if (i < 18 && ft_strequ(tab[0], g_child[i].name))
		ret = g_child[i].f(r, tab[1]);
	return (free_tab(tab, ret));
}
