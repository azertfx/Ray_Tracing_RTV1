/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 05:57:57 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/04 00:50:13 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void	wood(t_vect pt, t_vect *color)
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
