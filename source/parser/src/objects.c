/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:20:15 by hastid            #+#    #+#             */
/*   Updated: 2020/11/08 19:42:18 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_width(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, WID_SET))
	{
		if (get_double(&(r->o->width), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= WID_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_height(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, HEI_SET))
	{
		if (get_double(&(r->o->height), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= HEI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_negative(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, NEG_SET))
	{
		if (get_int(&(r->o->neg), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= NEG_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_rotation(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, ROT_SET))
	{
		if (get_vector(&r->o->rot, v, ROTAT) == ERROR)
			return (ERROR);
		r->o->opt |= ROT_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_reflection(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, REF_SET) && !IS_SET(r->o->opt, TCP_SET))
	{
		if (get_int(&(r->o->rfl), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= REF_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_translation(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, TRA_SET))
	{
		if (get_vector(&r->o->tra, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= TRA_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_transparence(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, TCP_SET) && !IS_SET(r->o->opt, REF_SET))
	{
		if (get_int(&(r->o->trs), v, DIST) == ERROR)
			return (ERROR);
		r->o->opt |= TCP_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_slice(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, SLC_SET))
	{
		if (get_int(&(r->o->slc), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= SLC_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_upordown(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, UOD_SET))
	{
		if (get_int(&(r->o->uod), v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= UOD_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_limit(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, LIM_SET))
	{
		if (get_vector(&r->o->lim, v, NONE) == ERROR)
			return (ERROR);
		r->o->opt |= LIM_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

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

int	parse_objects(t_rt *r, char **tab)
{
	int				i;
	int				ret;
	static t_child	c_child[18] = {
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

	ret = ERROR;
	i = -1;
	while (++i < 18)
		if (ft_strequ(tab[0], c_child[i].name))
			break ;
	if (i < 18 && ft_strequ(tab[0], c_child[i].name))
		ret = c_child[i].f(r, tab[1]);
	return (free_tab(tab, ret));
}
