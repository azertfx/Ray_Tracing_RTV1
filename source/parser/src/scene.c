/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:27:58 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 09:43:32 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_ambiance(t_rt *r, char *v)
{
	if (!IS_SET(r->s.opt, AMB_SET))
	{
		if (!get_double(&(r->s.amb), v, DIST))
			return (ERROR);
		r->s.opt |= AMB_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_anti_aliasing(t_rt *r, char *v)
{
	if (!IS_SET(r->s.opt, AAL_SET))
	{
		if (!get_int(&(r->s.aal), v, DIST))
			return (ERROR);
		r->s.opt |= AAL_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_cartoon_effect(t_rt *r, char *v)
{
	if (!IS_SET(r->s.opt, CAE_SET))
	{
		if (!get_int(&(r->s.cef), v, DIST))
			return (ERROR);
		r->s.opt |= CAE_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_motion_blur(t_rt *r, char *v)
{
	if (!IS_SET(r->s.opt, MBL_SET))
	{
		if (!get_int(&(r->s.mbl), v, DIST))
			return (ERROR);
		r->s.opt |= MBL_SET;
		return (SUCCESS);
	}
	return (ERROR);
}

int	parse_scene(t_rt *r, char **tab)
{
	int				i;
	int				ret;
	static t_child	c_child[5] = {
		{"filters:", &add_filters},
		{"ambiance:", &add_ambiance},
		{"antialiasing:", &add_anti_aliasing},
		{"cartoon_effect:", &add_cartoon_effect},
		{"motion_blur:", &add_motion_blur},
	};

	ret = ERROR;
	i = -1;
	while (++i < 5)
		if (ft_strequ(tab[0], c_child[i].name))
			break ;
	if (i < 5 && ft_strequ(tab[0], c_child[i].name))
		ret = c_child[i].f(r, tab[1]);
	return (free_tab(tab, ret));
}
