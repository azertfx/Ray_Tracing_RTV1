/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 23:17:58 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/04 00:49:27 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "rt.h"
# pragma pack(push, 1)

typedef struct	s_bmp
{
	char		id[2];
	int			file_size;
	int			unused;
	int			offset;
	int			dib;
	int			width;
	int			height;
	char		plane[2];
	char		bpp[2];
	int			compression;
	int			raw_bitmap_size;
	int			resx;
	int			resy;
	int			number_of_colors;
	int			important_colors;
}				t_bmp;

# pragma pack(pop)
#endif
