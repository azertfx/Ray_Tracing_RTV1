/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:37:06 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/29 00:56:52 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_clear_and_draw(t_var *v)
{
	mlx_destroy_image(v->mlx.mlx_ptr, v->mlx.img_ptr);
	v->mlx.img_ptr = mlx_new_image(v->mlx.mlx_ptr, IMG_W, IMG_H);
	mlx_clear_window(v->mlx.mlx_ptr, v->mlx.win_ptr);
	ft_instruction(v);
	if (check_file(v))
		draw(*v);
	mlx_put_image_to_window(v->mlx.mlx_ptr, v->mlx.win_ptr,
							v->mlx.img_ptr, 210, 0);
}

void	other_files(int k, t_var *v)
{
	if (k == Q)
		v->event.file = "scenes/translation";
	else if (k == W)
		v->event.file = "scenes/rotation";
	else if (k == P)
		v->event.file = "scenes/camera_y";
	else if (k == L)
		v->event.file = "scenes/multi_spots";
	else if (k == R)
		v->event.file = "scenes/multi_objs_1";
	else if (k == T)
		v->event.file = "scenes/multi_objs_2";
}

int		ft_keys_hook(int k, t_var *v)
{
	if (k == 53)
	{
		free_all_object(v);
		exit(0);
	}
	else if (k == O)
		v->event.file = v->event.file_origin;
	else if (k == S)
		v->event.file = "scenes/sphere";
	else if (k == X)
		v->event.file = "scenes/plane";
	else if (k == Y)
		v->event.file = "scenes/cone";
	else if (k == Z)
		v->event.file = "scenes/cylinder";
	else if (k == Q || k == W || k == P ||
				k == L || k == R || k == T)
		other_files(k, v);
	ft_clear_and_draw(v);
	return (0);
}
