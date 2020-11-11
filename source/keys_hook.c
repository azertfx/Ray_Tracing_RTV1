/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:37:06 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/08 05:19:42 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_clear_and_draw(t_rt *v)
{
	mlx_destroy_image(v->m.mlx_ptr, v->m.img_ptr);
	v->m.img_ptr = mlx_new_image(v->m.mlx_ptr, IMG_W, IMG_H);
	mlx_clear_window(v->m.mlx_ptr, v->m.win_ptr);
	ft_instruction(v);
	if (check_file(v))
		draw(*v);
	mlx_put_image_to_window(v->m.mlx_ptr, v->m.win_ptr,
							v->m.img_ptr, 210, 0);
}

void	move_camera(int k, t_rt *v)
{
	if (k == 126)
		v->event.move_z -= 2;
	else if (k == 125)
		v->event.move_z += 2;
	else if (k == 124)
		v->event.move_x += 2;
	else if (k == 123)
		v->event.move_x -= 2;
	else if (k == 87)
		v->event.rot_y += 2;
	else if (k == 84)
		v->event.rot_y -= 2;
	else if (k == 85)
		v->event.rot_x += 2;
	else if (k == 83)
		v->event.rot_x -= 2;
}

void	other_files(int k, t_rt *v)
{
	if (k == Q)
		v->event.file = "scenes/parallel_light.yaml";
	else if (k == W)
		v->event.file = "scenes/reflection.yaml";
	else if (k == P)
		v->event.file = "scenes/refraction.yaml";
	else if (k == L)
		v->event.file = "scenes/trans_shadow.yaml";
	else if (k == R)
		v->event.file = "scenes/textures.yaml";
	else if (k == T)
		v->event.file = "scenes/composed_elements.yaml";
	else if (k == SPACE)
		save_bmp_image(v->m);
	else
		move_camera(k, v);
}

int		ft_keys_hook(int k, t_rt *v)
{
	if (k == 53)
	{
		// free_all_object(v);
		exit(0);
	}
	else if (k == O)
		v->event.file = v->event.file_origin;
	else if (k == S)
		v->event.file = "scenes/objects.yaml";
	else if (k == X)
		v->event.file = "scenes/light.yaml";
	else if (k == Y)
		v->event.file = "scenes/limited_objs.yaml";
	else if (k == Z)
		v->event.file = "scenes/disruptions.yaml";
	else
		other_files(k, v);
	ft_clear_and_draw(v);
	return (0);
}
