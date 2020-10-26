/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:05:07 by hezzahir          #+#    #+#             */
/*   Updated: 2020/10/20 11:05:11 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "rtv1.h"

/*
**	Disruption id :
**				*) id = 1 : Checkboard
**				*) id = 2 : XOR
**				*) id = 3 : Perlin
**				*) id = 4 : Perlin sexy 🤩😍
*/


/*
** Noice checkboard / Damier
*/
void    checkboard(t_vect point, t_vect *color, double x)
{
	float       sines;

	sines = sin(x * point.x) * sin(x * point.y) * sin(x * point.z);
	if (sines < 0)
		*color = (t_vect){0.0, 0.0, 0.0};
	else
		*color = (t_vect){255.0, 255.0, 255.0};
}

/*
** Noice XOR
*/

t_vect		noise_xor(t_vect color, int x, int y)
{
	uint8_t	c;

	c = (y ^ x);
	color.x = 255 - c;
	color.y = c;
	color.z = c % 128;
	return (color);
}

void		apply_noise(t_point *p)
{
	if (p->obj->dsp == CHECKBOARD)
		checkboard(p->p_inter, &p->p_color, 0.3);
	else if (p->obj->dsp == XOR)
		p->p_color = noise_xor(p->p_color, p->p_inter.x , p->p_inter.y);
}
