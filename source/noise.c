/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:05:07 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/13 22:59:54 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		generate_noise(void)
{
	int	x;
	int	y;
	int	z;

	x = -1;
	y = -1;
	z = -1;
	while (z++ < NOISEDEPTH)
		while (y++ < NOISEHEIGHT)
			while (x++ < NOISEWIDTH)
				g_noise[z][y][x] = (rand() % 32768) / 32768.0;
	x = 0;
	while (x < 256)
	{
		g_p[x] = rand() % 256;
		g_p[256 + x] = g_p[x];
		x++;
	}
}

void		checkboard(t_vect point, t_vect *color, double x)
{
	float	sines;

	sines = sin(x * point.x) * sin(x * point.y) * sin(x * point.z);
	if (sines < 0)
		*color = (t_vect){35.0, 67.0, 136.0};
	else
		*color = (t_vect){31.0, 151.0, 206.0};
}

t_vect		noise_xor(t_vect color, t_vect v)
{
	uint8_t	c;

	c = ((int)v.x ^ (int)v.y ^ (int)v.z);
	color.x = 255 - c;
	color.y = c;
	color.z = c % 128;
	return (color);
}

void		perlin(t_vect v, t_vect *color)
{
	double	n;

	n = pnoise(v.x, v.y, v.z);
	n = n - floor(n);
	color->x = floor(255 * n);
	color->y = floor(255 * n);
	color->z = floor(255 * n);
}

void		apply_noise(t_point *p)
{
	if (p->obj->what_found == -1)
	{
		if (p->obj->dsp == CHECKBOARD)
			checkboard(p->p_inter, &p->p_color, 0.3);
		else if (p->obj->dsp == XOR)
			p->p_color = noise_xor(p->p_color, p->p_inter);
		else if (p->obj->dsp == WOOD)
			wood(p->p_inter, &p->p_color, 10);
		else if (p->obj->dsp == PERLIN)
			perlin(p->p_inter, &p->p_color);
	}
}
