/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise2_norme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:05:07 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/05 19:48:36 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct	s_cordin
{
	int	x;
	int	y;
	int	z;
}				t_cordin;


double smooth_noise(double x, double y, double z)
{
	t_vect		fract;
	t_cordin	p;
	t_cordin	p1;
	double		value;

	/*
	** get fractional part of x, y && z
	*/
	value = 0.0;
	fract.x = x - (int)x;
	fract.y = y - (int)y;
	fract.z = z - (int)z;
	/*
	** wrap around
	*/

	p.x = ((int)x + noiseWidth) % noiseWidth;
	p.y = ((int)y + noiseHeight) % noiseHeight;
	p.z = ((int)z + noiseDepth) % noiseDepth;
	/*
	** neighbor values
	*/
	p1.x = (p.x + noiseWidth - 1) % noiseWidth;
	p1.y = (p.y + noiseHeight - 1) % noiseHeight;
	p1.z = (p.z + noiseDepth - 1) % noiseDepth;
	/*
	** smooth the noise with bilinear interpolation
	*/
	value += fract.x * fract.y * fract.z * noise[p.z][p.y][p.x];
	value += fract.x * (1 - fract.y) * fract.z * noise[p.z][p1.y][p.x];
	value += (1 - fract.x) * fract.y * fract.z * noise[p.z][p.y][p1.x];
	value += (1 - fract.x) * (1 - fract.y) * fract.z * noise[p.z][p1.y][p1.x];
	value += fract.x * fract.y * (1 - fract.z) * noise[p1.z][p.y][p.x];
	value += fract.x * (1 - fract.y) * (1 - fract.z) * noise[p1.z][p1.y][p.x];
	value += (1 - fract.x) * fract.y * (1 - fract.z) * noise[p1.z][p.y][p1.x];
	value += (1 - fract.x) * (1 - fract.y) * (1 - fract.z) * noise[p1.z][p1.y][p1.x];
	return (value);
}

double turbulence(double x, double y, double z, double size)
{
	double	value;
	double	initialSize;

	value = 0.0;
	initialSize = size;
	while (size >= 1)
	{
		value += smooth_noise(x / size, y / size, z / size) * size;
		size /= 2.0;
	}

	return (128.0 * value / initialSize);
}

void	wood(t_vect pt, t_vect *color)
{
	t_vect	value;
	double xyPeriod;  //number of rings
	double turbPower; //makes twists
	double turbSize; //initial size of the turbulence
	double sineValue;
	double distValue;

	xyPeriod = 10;
	turbPower = 0.7;
	turbSize = 12465.0;
	value.x = (pt.x - noiseWidth / 2) / (double)noiseWidth;
	value.y= (pt.y - noiseHeight / 2) / (double)noiseHeight;
	value.z= (pt.z - noiseDepth / 2) / (double)noiseDepth;
	distValue = sqrt(value.x * value.x + value.y * value.y+ value.z* value.z)
	 		+ turbPower * turbulence(pt.x, pt.y, pt.z, turbSize) / 256.0;
	sineValue = 128.0 * fabs(sin(2 * xyPeriod * distValue * 3.14159));
	color->x = (uint8_t)(80 + sineValue);
	color->y = (uint8_t)(30 + sineValue);
	color->z = 30;
}
