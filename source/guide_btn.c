/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_btn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:11:07 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/04 00:49:48 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_btn_content(t_rt *v)
{
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 113, 0xFFFFFF, "O");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 163, 0xFFFFFF, "S");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 113, 0xFFFFFF, ORI);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 163, 0xFFFFFF, SPH);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 213, 0xFFFFFF, "X");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 263, 0xFFFFFF, "Y");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 213, 0xFFFFFF, PLA);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 263, 0xFFFFFF, CON);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 313, 0xFFFFFF, "Z");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 363, 0xFFFFFF, "Q");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 313, 0xFFFFFF, CYL);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 363, 0xFFFFFF, TRA);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 413, 0x00EAFF, "W");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 463, 0xFFAA85, "P");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 413, 0x00EAFF, ROT);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 463, 0xFFAA85, CAM);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 513, 0xFFC600, "L");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 513, 0xFFC600, MULTIS);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 563, 0x69FF97, "R");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 563, 0x69FF97, MULTI1);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 613, 0xFF96F9, "T");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 613, 0xFF96F9, MULTI2);
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 30, 663, 0xFF0000, "E");
	mlx_string_put(v->m.mlx_ptr, v->m.win_ptr, 60, 663, 0xFF0000, "Exit");
}

void	ft_draw_btn(t_rt *v, int x, int y)
{
	int i;

	i = 120 + y;
	while (i < 150 + y)
	{
		mlx_pixel_put(v->m.mlx_ptr, v->m.win_ptr, 10 + x, i, 0xFFFFFF);
		mlx_pixel_put(v->m.mlx_ptr, v->m.win_ptr, 40 + x, i++, 0xFFFFFF);
	}
	i = 10 + x;
	while (i < 40 + x)
	{
		mlx_pixel_put(v->m.mlx_ptr, v->m.win_ptr, i, 120 + y, 0xFFFFFF);
		mlx_pixel_put(v->m.mlx_ptr, v->m.win_ptr, i++, 150 + y, 0xFFFFFF);
	}
}
