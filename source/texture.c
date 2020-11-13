/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:45:16 by hastid            #+#    #+#             */
/*   Updated: 2020/11/13 12:17:43 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	constrector(double x, double y, double z)
{
	t_vect vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}

int		add_texture(t_rt *rt)
{
	char	txt[50];
	t_obj	*temp;

	temp = rt->o;
	while (temp)
	{
		if (temp->txt.t)
		{
			if (temp->txt.t == 1)
				ft_strcpy(txt, "xpm/earth.xpm");
			else if (temp->txt.t == 3)
				ft_strcpy(txt, "xpm/4.xpm");
			else
				ft_strcpy(txt, "xpm/5.xpm");
			temp->txt.img = mlx_xpm_file_to_image(rt->m.mlx_ptr,
				txt, &temp->txt.width, &temp->txt.height);
			if (!temp->txt.img)
				return (0);
			temp->txt.buf = (int *)mlx_get_data_addr(temp->txt.img,
			&rt->m.bpp, &rt->m.size_l, &rt->m.endian);
		}
		temp = temp->next;
	}
	return (1);
}

int		color_texture(t_point *p)
{
	int		i;
	int		j;
	t_vect	pol;

	pol = ft_vect_sub(p->obj->ori, constrector(ft_vect_dot(p->p_inter,
	constrector(1.0, 0.0, 0.0)), ft_vect_dot(p->p_inter,
	constrector(0.0, -1.0, 0.0)), ft_vect_dot(p->p_inter,
	constrector(0.0, 0.0, 1.0))));
	get_angle(p->obj, pol);
	i = p->obj->txt.um * p->obj->txt.width;
	j = (1.0 - p->obj->txt.vm) * p->obj->txt.height - 0.001;
	i = (i < 0) ? 0 : i;
	j = (j < 0) ? 0 : j;
	i = (i > p->obj->txt.width - 1) ? p->obj->txt.width - 1 : i;
	j = (j > p->obj->txt.height - 1) ? p->obj->txt.height - 1 : j;
	if (p->obj->txt.buf[j * p->obj->txt.width + i] == -16777216)
		return (0);
	p->p_color.x = (p->obj->txt.buf[j * p->obj->txt.width + i] >> 16) & 0xFF;
	p->p_color.y = (p->obj->txt.buf[j * p->obj->txt.width + i] >> 8) & 0xFF;
	p->p_color.z = p->obj->txt.buf[j * p->obj->txt.width + i] & 0xFF;
	return (1);
}
