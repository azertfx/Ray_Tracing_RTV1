/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:05:07 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/05 22:43:30 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Disruption id :
**				*) id = 1 : Checkboard
**				*) id = 2 : XOR
**				*) id = 3 : Perlin
**				*) id = 4 : Perlin sexy 🤩😍
**				*) id = 4 :
*/

void	generate_noise(void)
{
	int	x;
	int	y;
	int	z;

	x = -1;
	y = -1;
	z = -1;
	while (z++ < noiseDepth)
		while (y++ < noiseHeight)
			while (x++ < noiseWidth)
				noise[z][y][x] = (rand() % 32768) / 32768.0;
}

/*
** Noice checkboard / Damier
*/
void	checkboard(t_vect point, t_vect *color, double x)
{
	float	sines;

	sines = sin(x * point.x) * sin(x * point.y) * sin(x * point.z);
	if (sines < 0)
		*color = (t_vect){35.0, 67.0, 136.0};
	else
		*color = (t_vect){31.0, 151.0, 206.0};
}

/*
** Noice XOR
*/

t_vect		noise_xor(t_vect color, t_vect v)
{
	uint8_t	c;

	c = ((int) v.x ^ (int) v.y ^ (int) v.z);
	color.x = 255 - c;
	color.y = c;
	color.z = c % 128;
	return (color);
}


void		apply_noise(t_point *p)
{
  	//printf("|%d|\n", p->obj->dsp);
	if (p->obj->dsp == CHECKBOARD)
		checkboard(p->p_inter, &p->p_color, 0.3);
	else if (p->obj->dsp == XOR)
		p->p_color = noise_xor(p->p_color, p->p_inter);
	else if (p->obj->dsp == WOOD)
		wood(p->p_inter, &p->p_color, 10);
	/*else if (p->obj->dsp == PERLIN)
		perlin(p->p_inter, &p->p_color);*/
}
