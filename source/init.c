/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 04:51:21 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/11/04 04:55:04 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void    init_event(t_rt *v, char *file)
{
    v->event.file = file;
	v->event.file_origin = file;
	v->event.move_z = 0;
	v->event.move_x = 0;
	v->event.rot_y = 0;
	v->event.rot_x = 0;
}

void    init_mlx(t_rt *v)
{
    v->m.mlx_ptr = mlx_init();
	v->m.win_ptr = mlx_new_window(v->m.mlx_ptr, WIN_W, IMG_H, "1337 RT");
	v->m.img_ptr = mlx_new_image(v->m.mlx_ptr, IMG_W, IMG_H);
	v->m.img_data = (unsigned char *)mlx_get_data_addr(
		v->m.img_ptr, &v->m.bpp, &v->m.size_l, &v->m.endian);
}

int		check_file(t_rt *v)
{
/*
**	free_all_object(v);
*/
	if (!v->event.file || !parse_file(v->event.file, v))
	{
/*
**	free_all_object(v);
*/
		ft_putendl("Try Again! 🙄");
		return (0);
	}
	return (1);
}
