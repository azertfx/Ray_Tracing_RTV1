/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 04:00:19 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/14 04:09:53 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		rad(double x)
{
	return ((x * M_PI / 180));
}

double		px_x(double x)
{
	return ((x + 0.5) * 2.0 / (double)IMG_W - 1.0);
}

double		px_y(double y)
{
	return (1.0 - (y + 0.5) * 2.0 / (double)IMG_H);
}
