/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:53:03 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/24 13:20:40 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_draw_rec(t_var *v)
{
	int i;

	i = 0;
	while (i < 700)
	{
		if (i % 5 == 0)
			mlx_pixel_put(v->mlx.mlx_ptr, v->mlx.win_ptr, 210, i, 0xFFF000);
		i++;
	}
	i = 20;
	while (i < 85)
	{
		mlx_pixel_put(v->mlx.mlx_ptr, v->mlx.win_ptr, 20, i, 0x0FFFFF);
		mlx_pixel_put(v->mlx.mlx_ptr, v->mlx.win_ptr, 190, i, 0x0FFFFF);
		i += 3;
	}
	i = 20;
	while (i < 190)
	{
		mlx_pixel_put(v->mlx.mlx_ptr, v->mlx.win_ptr, i, 20, 0x0FFFFF);
		mlx_pixel_put(v->mlx.mlx_ptr, v->mlx.win_ptr, i, 85, 0x0FFFFF);
		i += 3;
	}
}

void	ft_logo_draw(t_var *v, int y, int x, int n)
{
	int i;
	int j;
	int c;

	c = 0;
	while (c < n)
	{
		j = 0;
		while (j < 5)
		{
			i = 0;
			while (i < 5)
			{
				if (i % 3 == 0 && j % 3 == 0)
					mlx_pixel_put(v->mlx.mlx_ptr, v->mlx.win_ptr, x +
							j + c * 5, y + i, 0xFFFFFF);
				i++;
			}
			j++;
		}
		c++;
	}
}

void	ft_draw_logo_b(t_var *v)
{
	ft_logo_draw(v, 35, 110, 4);
	ft_logo_draw(v, 40, 125, 1);
	ft_logo_draw(v, 45, 125, 1);
	ft_logo_draw(v, 50, 110, 4);
	ft_logo_draw(v, 55, 125, 1);
	ft_logo_draw(v, 60, 125, 1);
	ft_logo_draw(v, 65, 110, 4);
	ft_logo_draw(v, 35, 140, 4);
	ft_logo_draw(v, 40, 140, 1);
	ft_logo_draw(v, 40, 155, 1);
	ft_logo_draw(v, 45, 140, 1);
	ft_logo_draw(v, 45, 155, 1);
	ft_logo_draw(v, 45, 155, 1);
	ft_logo_draw(v, 50, 155, 1);
	ft_logo_draw(v, 55, 155, 1);
	ft_logo_draw(v, 60, 155, 1);
	ft_logo_draw(v, 65, 155, 1);
}

void	ft_draw_logo_a(t_var *v)
{
	ft_logo_draw(v, 35, 50, 3);
	ft_logo_draw(v, 40, 50, 1);
	ft_logo_draw(v, 40, 60, 1);
	ft_logo_draw(v, 45, 60, 1);
	ft_logo_draw(v, 50, 60, 1);
	ft_logo_draw(v, 55, 60, 1);
	ft_logo_draw(v, 60, 60, 1);
	ft_logo_draw(v, 65, 55, 3);
	ft_logo_draw(v, 35, 80, 4);
	ft_logo_draw(v, 40, 95, 1);
	ft_logo_draw(v, 45, 95, 1);
	ft_logo_draw(v, 50, 80, 4);
	ft_logo_draw(v, 55, 95, 1);
	ft_logo_draw(v, 60, 95, 1);
	ft_logo_draw(v, 65, 80, 4);
}

void	ft_instruction(t_var *v)
{
	ft_draw_rec(v);
	ft_draw_logo_a(v);
	ft_draw_logo_b(v);
	ft_draw_btn(v, 10, -10);
	ft_draw_btn(v, 10, 40);
	ft_draw_btn(v, 10, 90);
	ft_draw_btn(v, 10, 140);
	ft_draw_btn(v, 10, 190);
	ft_draw_btn(v, 10, 240);
	ft_draw_btn(v, 10, 290);
	ft_draw_btn(v, 10, 340);
	ft_draw_btn(v, 10, 390);
	ft_draw_btn(v, 10, 440);
	ft_draw_btn(v, 10, 490);
	ft_draw_btn(v, 10, 540);
	ft_btn_content(v);
}
