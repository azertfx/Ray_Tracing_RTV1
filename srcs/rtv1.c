/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:23:37 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/29 01:01:40 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_pixel_color(t_var *v, int i, int j, t_vector color)
{
	v->mlx.img_data[(j * IMG_W + i) * 4 + 0] =
							fmin(255, fmax(0, pow(color.z, 1 / 2.2)));
	v->mlx.img_data[(j * IMG_W + i) * 4 + 1] =
							fmin(255, fmax(0, pow(color.y, 1 / 2.2)));
	v->mlx.img_data[(j * IMG_W + i) * 4 + 2] =
							fmin(255, fmax(0, pow(color.x, 1 / 2.2)));
	v->mlx.img_data[(j * IMG_W + i) * 4 + 3] =
							0;
}

void	*draw_threads(void *t)
{
	t_var		*v;
	int			i;
	int			j;
	double		x;
	double		y;

	v = (t_var *)t;
	j = v->thread.start;
	while (j < v->thread.end)
	{
		y = 1. - 2. * (double)j / (double)IMG_H;
		i = 0;
		while (i < IMG_W)
		{
			x = 2. * (double)i / (double)IMG_W - 1.;
			generate_camera_ray(v, &v->thread.ray, y, x);
			v->thread.color = (t_vector){0, 0, 0};
			v->thread.color = ray_trace(v, &v->thread.ray, &v->thread.color);
			set_pixel_color(v, i, j, v->thread.color);
			i++;
		}
		j++;
	}
	return (NULL);
}

void	draw(t_var v)
{
	t_var		t[THREADS];
	pthread_t	id[THREADS];
	int			i;
	int			j;

	i = 0;
	v.thread.start = 0;
	generate_camera(&v);
	while (i < THREADS)
	{
		ft_memcpy(&t[i], &v, sizeof(t_var));
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

int		check_file(t_var *v)
{
	free_all_object(v);
	if (!v->event.file || !parse_file(v->event.file, v))
	{
		free_all_object(v);
		ft_putendl("Try Again!");
		return (0);
	}
	return (1);
}

int		rtv1(t_var *v, char *file)
{
	ft_bzero(v, sizeof(t_var));
	v->event.file = file;
	v->event.file_origin = file;
	if (!check_file(v))
		return (0);
	v->mlx.mlx_ptr = mlx_init();
	v->mlx.win_ptr = mlx_new_window(v->mlx.mlx_ptr, WIN_W, IMG_H, "1337 RTV1");
	v->mlx.img_ptr = mlx_new_image(v->mlx.mlx_ptr, IMG_W, IMG_H);
	v->mlx.img_data = (unsigned char *)mlx_get_data_addr(
			v->mlx.img_ptr, &v->mlx.bpp, &v->mlx.size_l, &v->mlx.endian);
	ft_instruction(v);
	draw(*v);
	mlx_hook(v->mlx.win_ptr, 2, 0, ft_keys_hook, v);
	mlx_put_image_to_window(v->mlx.mlx_ptr, v->mlx.win_ptr, v->mlx.img_ptr,
				210, 0);
	mlx_loop(v->mlx.mlx_ptr);
	return (1);
}
