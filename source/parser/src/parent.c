/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:50:16 by hastid            #+#    #+#             */
/*   Updated: 2020/11/06 01:50:12 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_object(t_rt *r)
{
	t_obj *o;
	t_obj *tmp;

	if (!(o = (t_obj *)malloc(sizeof(t_obj))))
		return (ERROR);
	o->id = r->id;
	tmp = r->o;
	r->o = o;
	o->opt = 0;
	o->rfl = 0;
	o->trs = 0;
	o->neg = 0;
	o->slc = 0;
	o->txt.t = 0;
	o->dsp = -1;
	o->width = -1;
	o->height = -1;
	o->next = tmp;
	return (SUCCESS);
}

int	add_camera(t_rt *r)
{
	if (r->c)
		return (ERROR);
	if (!(r->c = (t_cam *)malloc(sizeof(t_cam))))
		return (ERROR);
	r->c->opt = 0;
	return (SUCCESS);
}

int	add_light(t_rt *r)
{
	t_light *l;
	t_light *tmp;

	if (!(l = (t_light *)malloc(sizeof(t_light))))
		return (ERROR);
	tmp = r->l;
	r->l = l;
	l->opt = 0;
	l->ang = 0;
	l->id = POINT;
	l->next = tmp;
	return (SUCCESS);
}

int	add_scene(t_rt *r)
{
	r->s.opt = 0;
	r->s.aal = 0;
	r->s.cef = 0;
	r->s.fil = 0;
	r->s.amb = 80;
	return (SUCCESS);
}

int	parse_parent(char *line, t_rt *r)
{
	int				i;
	static t_parent	parents[P_COUNT] = {
		{"light:", &add_light},
		{"camera:", &add_camera},
		{"cone:", &add_object},
		{"plane:", &add_object},
		{"sphere:", &add_object},
		{"cylinder:", &add_object},
		{"paraboloid:", &add_object},
		{"disc:", &add_object},
		{"square:", &add_object},
		{"hemisphere:", &add_object},
		{"scene:", &add_scene},
	};

	i = -1;
	while (++i < P_COUNT)
		if (ft_strequ(line, parents[i].p))
		{
			r->id = i;
			return (parents[i].f(r));
		}
	return (ERROR);
}
