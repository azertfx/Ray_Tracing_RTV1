/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:23:30 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 13:49:02 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_parser_two(void)
{
	g_amb = 1 << 15;
	g_fil = 1 << 16;
	g_aal = 1 << 17;
	g_cae = 1 << 18;
	g_dof = 1 << 19;
	g_ang = 1 << 20;
	g_slc = 1 << 21;
	g_uod = 1 << 22;
	g_lim = 1 << 23;
	g_dsp = 1 << 24;
	g_lmo = 1 << 25;
	g_lmt = 1 << 26;
	g_mbl = 1 << 27;
	g_txt = 1 << 28;
}

void	init_parser(void)
{
	g_ori = 1;
	g_tar = 1 << 1;
	g_fov = 1 << 2;
	g_col = 1 << 3;
	g_pow = 1 << 4;
	g_ray = 1 << 5;
	g_axi = 1 << 6;
	g_tra = 1 << 7;
	g_rot = 1 << 8;
	g_lgt = 1 << 9;
	g_wid = 1 << 10;
	g_hei = 1 << 11;
	g_neg = 1 << 12;
	g_ref = 1 << 13;
	g_tcp = 1 << 14;
	init_parser_two();
}

int		add_fov(t_rt *r, char *v)
{
	if (r->id == CAMERA && !is_set(r->c->opt, g_fov))
	{
		if (get_double(&(r->c->fov), v, ANGL) == ERROR)
			return (ERROR);
		r->c->opt |= g_fov;
		return (SUCCESS);
	}
	return (ERROR);
}

int		add_target(t_rt *r, char *v)
{
	if (r->id == CAMERA && !is_set(r->c->opt, g_tar))
	{
		if (get_vector(&r->c->tar, v, NONE) == ERROR)
			return (ERROR);
		r->c->opt |= g_tar;
		return (SUCCESS);
	}
	return (ERROR);
}

int		parse_camera(t_rt *r, char **tab)
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
