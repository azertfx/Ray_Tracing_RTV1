/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:18:26 by hastid            #+#    #+#             */
/*   Updated: 2020/10/21 18:43:45 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
int	add_axis(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, AXI_SET)
			&& get_vector(&r->l->axi, v, NONE))
	{
		r->l->opt |= AXI_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 6 && !IS_SET(r->o->opt, AXI_SET)
			&& get_vector(&r->o->axi, v, NONE))
	{
		r->o->opt |= AXI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_color(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, COL_SET)
			&& get_vector(&r->l->col, v, COLOR))
	{
		r->l->opt |= COL_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 6 && !IS_SET(r->o->opt, COL_SET)
			&& get_vector(&r->o->col, v, COLOR))
	{
		r->o->opt |= COL_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_origin(t_rt *r, char *v)
{
	if (r->id == LIGHT && !IS_SET(r->l->opt, ORI_SET)
			&& get_vector(&r->l->ori, v, NONE))
	{
		r->l->opt |= ORI_SET;
		return (SUCCESS);
	}
	if (r->id == CAMERA && !IS_SET(r->c->opt, ORI_SET)
			&& get_vector(&r->c->ori, v, NONE))
	{
		r->c->opt |= ORI_SET;
		return (SUCCESS);
	}
	if (r->id >= 2 && r->id <= 6 && !IS_SET(r->o->opt, ORI_SET)
			&& get_vector(&r->o->ori, v, NONE))
	{
		r->o->opt |= ORI_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

// objects

int	add_ray(t_rt *r, char *v)
{
	if (!IS_SET(r->o->opt, RAY_SET))
	{
        if (get_double(&(r->o->ray), v, DIST) == ERROR)
            return (ERROR);
		r->o->opt |= RAY_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

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
	if (!IS_SET(r->o->opt, REF_SET))
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
	if (!IS_SET(r->o->opt, TCP_SET))
	{
        if (get_int(&(r->o->trs), v, DIST) == ERROR)
            return (ERROR);
		r->o->opt |= TCP_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	parse_objects(t_rt *r, char **tab)
{
	int				i;
	int				ret;
	static t_child	c_child[11] = {
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
	};

	ret = ERROR;
	i = -1;
	while (++i < 11)
		if (ft_strequ(tab[0], c_child[i].name))
			break ;
	if (i < 11 && ft_strequ(tab[0], c_child[i].name))
		ret = c_child[i].f(r, tab[1]);
	return (free_tab(tab, ret));
}

// camera
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

//lights

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
	if (r->id == LIGHT && !IS_SET(r->l->opt, LIGHt_T))
	{
        if (!ft_strcmp(v, "POINT"))
            r->l->id = POINT;
        else if (!ft_strcmp(v, "DIRECT"))
            r->l->id = DIRECT;
        else if (!ft_strcmp(v, "PARALLEL"))
            r->l->id = PARALLEL;
        else
            return (ERROR);
        r->l->opt |= LIGHt_T;
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

int	add_child(t_rt *r, char **tab)
{
	if (!tab[1])
		return (free_tab(tab, ERROR));
	if (r->id == CAMERA)
		return (parse_camera(r, tab));
	// else if (r->id == SCENE)
	// 	return (parse_scene(r, tab));
	else if (r->id == LIGHT)
		return (parse_lights(r, tab));
	else
		return (parse_objects(r, tab));
	return (free_tab(tab, ERROR));
}
