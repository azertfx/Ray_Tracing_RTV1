/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:23:37 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/08 21:13:35 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	ray_trace(t_rt *v, t_ray *ray, t_vect *color, t_vect depth)
{
	if (intersection_checker(v, *ray, &v->point) && (depth.x < 4))
	{
		objects_normal(*ray, &v->point);
		apply_noise(&v->point);
		get_pixel_color(v, &v->point.p_color);
		if (depth.x != 0)
			v->point.p_color =
				ft_vect_div_nbr(v->point.p_color, depth.y ? depth.y : depth.z);
		*color = ft_vect_add(*color, v->point.p_color);
		if (v->point.obj->rfl || v->point.obj->trs)
		{
			check_refl_refr(v, ray, &depth);
			depth.x++;
			ft_vect_norm(&ray->dir);
			ray->ori = ft_vect_add(v->point.p_inter,
						ft_vect_mult_nbr(ray->dir, 0.5));
			ray_trace(v, ray, color, depth);
		}
	}
	return (*color);
}

void	rt_core(t_rt *v, double *axis)
{
	t_vect	depth;
	t_vect	final_color;
	int		r;
	int		visual_effect;

	v->thread.color = (t_vect){0, 0, 0};
	final_color = (t_vect){0, 0, 0};
	depth = (t_vect){0, 0, 0};
	r = 0;
	visual_effect = (v->s.cef || v->s.aal) ? 1 : 0;
	if (visual_effect)
		visual_effect = 9;
	else
		visual_effect = 1;
	while (r < visual_effect)
	{
		generate_camera_ray(v, &v->thread.ray, axis, r);
		final_color = ray_trace(v, &v->thread.ray, &v->thread.color, depth);
		v->thread.color = ft_vect_div_nbr(final_color,
							(visual_effect == 1) ? 1 : 2);
		r++;
	}
}

void	*draw_threads(void *t)
{
	t_rt	*v;
	double	i;
	double	j;
	double	axis[2];

	v = (t_rt *)t;
	j = v->thread.start;
	while (j < v->thread.end)
	{
		axis[1] = (double)j;
		i = 0;
		while (i < IMG_W)
		{
			axis[0] = (double)i;
			rt_core(v, axis);
			set_pixel_color(v, i, j, v->thread.color);
			i++;
		}
		j++;
	}
	return (NULL);
}

void	draw(t_rt v)
{
	t_rt		t[THREADS];
	pthread_t	id[THREADS];
	int			i;
	int			j;

	i = 0;
	v.thread.start = 0;
	add_texture(&v);
	generate_camera(&v);
	while (i < THREADS)
	{
		ft_memcpy(&t[i], &v, sizeof(t_rt));
		t[i].thread.start = v.thread.start;
		t[i].thread.end = IMG_H / THREADS + v.thread.start;
		pthread_create(&id[i], NULL, draw_threads, (void *)&t[i]);
		v.thread.start = t[i].thread.end;
		i++;
	}
	j = 0;
	while (j < THREADS)
	{
		pthread_join(id[j], NULL);
		j++;
	}
}

int		rt(t_rt *v, char *file)
{
	ft_bzero(v, sizeof(t_rt));
	init_event(v, file);
	if (!check_file(v))
		return (0);
	init_mlx(v);
	show_loading(v);
	v->m.img_ptr = mlx_new_image(v->m.mlx_ptr, IMG_W, IMG_H);
	v->m.img_data = (unsigned char *)mlx_get_data_addr(
		v->m.img_ptr, &v->m.bpp, &v->m.size_l, &v->m.endian);
	ft_instruction(v);
	generate_noise();
	draw(*v);
	mlx_hook(v->m.win_ptr, 2, 0, ft_keys_hook, v);
	mlx_put_image_to_window(v->m.mlx_ptr, v->m.win_ptr, v->m.img_ptr,
					210, 0);
	mlx_loop(v->m.mlx_ptr);
	return (1);
}
