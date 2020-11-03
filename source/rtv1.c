/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:23:37 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/03 03:56:10 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_pixel_color(t_rt *v, int i, int j, t_vect color)
{
	filters(&color, 53);
	v->m.img_data[(j * IMG_W + i) * 4 + 0] = color.z;
	v->m.img_data[(j * IMG_W + i) * 4 + 1] = color.y;
	v->m.img_data[(j * IMG_W + i) * 4 + 2] = color.x;
	v->m.img_data[(j * IMG_W + i) * 4 + 3] = 0;
}

double	ft_random(double a, double b)
{
	return (rand() / (double)RAND_MAX) * (b - a) + a;
}

void	rt_core(t_rt *v, double x, double y)
{
	t_vect	depth;
	t_vect	final_color;
	int		r;
	int		anti_aliasing;

	v->thread.color = (t_vect){0, 0, 0};
	final_color = (t_vect){0, 0, 0};
	depth = (t_vect){0, 0, 0};
	r = 0;
	anti_aliasing = 0;
	if (anti_aliasing)
		anti_aliasing = 9;
	else
		anti_aliasing = 1;
	while (r < anti_aliasing)
	{
		generate_camera_ray(v, &v->thread.ray, y, x, r);
		final_color = ray_trace(v, &v->thread.ray, &v->thread.color, depth);
		v->thread.color = ft_vect_div_nbr(final_color,
							(anti_aliasing == 1) ? 1 : 2);
		r++;
	}
}

void	*draw_threads(void *t)
{
	t_rt	*v;
	double	i;
	double	j;
	double	x;
	double	y;

	v = (t_rt *)t;
	j = v->thread.start;
	while (j < v->thread.end)
	{
		y = (double)j;
		i = 0;
		while (i < IMG_W)
		{
			x = (double)i;
			rt_core(v, x, y);
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

int		check_file(t_rt *v)
{
	// free_all_object(v);
	if (!v->event.file || !parse_file(v->event.file, v))
	{
		// free_all_object(v);
		ft_putendl("Try Again! 🙄");
		return (0);
	}
	return (1);
}

int		rtv1(t_rt *v, char *file)
{
	ft_bzero(v, sizeof(t_rt));
	v->event.file = file;
	v->event.file_origin = file;
	if (!check_file(v))
		return (0);
	v->m.mlx_ptr = mlx_init();
	v->m.win_ptr = mlx_new_window(v->m.mlx_ptr, WIN_W, IMG_H, "1337 RTV1");
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
