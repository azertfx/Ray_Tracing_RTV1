/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 23:12:46 by hezzahir          #+#    #+#             */
/*   Updated: 2020/03/07 02:17:59 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_bmp	init_bmph(void)
{
	t_bmp		res;

	res.id[0] = 'B';
	res.id[1] = 'M';
	res.file_size = 54 + 4 * (int)WIN_W * (int)IMG_H;
	res.unused = 0;
	res.offset = 54;
	res.dib = 54 - 14;
	res.width = (int)IMG_W;
	res.height = -(int)IMG_H;
	res.plane[0] = 1;
	res.plane[1] = 0;
	res.bpp[0] = 32;
	res.bpp[1] = 0;
	res.compression = 0;
	res.raw_bitmap_size = 4 * (int)WIN_W * (int)IMG_H;
	res.resx = 0;
	res.resy = 0;
	res.number_of_colors = 0;
	res.important_colors = 0;
	return (res);
}

int				save_bmp_image(t_mlx image)
{
	t_bmp		img;
	int			file;

	file = open("rt.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	img = init_bmph();
	write(file, &img, 54);
	write(file, image.img_data, img.raw_bitmap_size);
	close(file);
	return (1);
}
