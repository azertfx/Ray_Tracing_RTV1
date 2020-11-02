/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:05:07 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/03 00:43:56 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "rtv1.h"

/*
**	Disruption id :
**				*) id = 1 : Checkboard
**				*) id = 2 : XOR
**				*) id = 3 : Perlin
**				*) id = 4 : Perlin sexy 🤩😍
**				*) id = 4 :
*/


void generate_noise()
{
  for(int z = 0; z < noiseDepth; z++)
  for(int y = 0; y < noiseHeight; y++)
  for(int x = 0; x < noiseWidth; x++)
  {
    noise[z][y][x] = (rand() % 32768) / 32768.0;
  }
}

/*
** Noice checkboard / Damier
*/
void    checkboard(t_vect point, t_vect *color, double x)
{
	float       sines;

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

double smoothNoise(double x, double y, double z)
{
  //get fractional part of x and y
  double fractX = x - (int)x;
  double fractY = y -(int)y;
  double fractZ = z - (int)z;

  //wrap around
  int x1 = ((int)x + noiseWidth) % noiseWidth;
  int y1 = ((int)y + noiseHeight) % noiseHeight;
  int z1 = ((int)z + noiseDepth) % noiseDepth;

  //neighbor values
  int x2 = (x1 + noiseWidth - 1) % noiseWidth;
  int y2 = (y1 + noiseHeight - 1) % noiseHeight;
  int z2 = (z1 + noiseDepth - 1) % noiseDepth;

  //smooth the noise with bilinear interpolation
  double value = 0.0;
  value += fractX     * fractY     * fractZ     * noise[z1][y1][x1];
  value += fractX     * (1 - fractY) * fractZ     * noise[z1][y2][x1];
  value += (1 - fractX) * fractY     * fractZ     * noise[z1][y1][x2];
  value += (1 - fractX) * (1 - fractY) * fractZ     * noise[z1][y2][x2];

  value += fractX     * fractY     * (1 - fractZ) * noise[z2][y1][x1];
  value += fractX     * (1 - fractY) * (1 - fractZ) * noise[z2][y2][x1];
  value += (1 - fractX) * fractY     * (1 - fractZ) * noise[z2][y1][x2];
  value += (1 - fractX) * (1 - fractY) * (1 - fractZ) * noise[z2][y2][x2];

  return value;
}

double turbulence(double x, double y, double z, double size)
{
  double value = 0.0, initialSize = size;

  while(size >= 1)
  {
    value += smoothNoise(x / size, y / size, z / size) * size;
    size /= 2.0;
  }

  return(128.0 * value / initialSize);
}

void	Wood(t_vect pt, t_vect *color)
{
	double xyPeriod = 10; //number of rings
	double turbPower = 0.7; //makes twists
	double turbSize = 12465.0; //initial size of the turbulence

	double xValue = (pt.x - noiseWidth / 2) / (double)noiseWidth;
    double yValue = (pt.y - noiseHeight / 2) / (double)noiseHeight;
	double zValue = (pt.z - noiseDepth / 2) / (double)noiseDepth;
    double distValue = sqrt(xValue * xValue + yValue * yValue + zValue * zValue) + turbPower *
	turbulence(pt.x, pt.y, pt.z, turbSize) / 256.0;
    double sineValue = 128.0 * fabs(sin(2 * xyPeriod * distValue * 3.14159));
    color->x = (uint8_t)(80 + sineValue);
    color->y = (uint8_t)(30 + sineValue);
    color->z = 30;
}
/*
void	perlin(t_vect pt, t_vect *color)
{

}*/

void		apply_noise(t_point *p)
{
  	//printf("|%d|\n", p->obj->dsp);
	if (p->obj->dsp == CHECKBOARD)
		checkboard(p->p_inter, &p->p_color, 0.3);
	else if (p->obj->dsp == XOR)
		p->p_color = noise_xor(p->p_color, p->p_inter);
	else if (p->obj->dsp == WOOD)
		Wood(p->p_inter, &p->p_color);
	/*else if (p->obj->dsp == PERLIN)
		perlin(p->p_inter, &p->p_color);*/
}
