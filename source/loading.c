/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 04:27:33 by hezzahir          #+#    #+#             */
/*   Updated: 2020/11/06 04:38:42 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*get_file_path(int i)
{
	char *file;

	file = NULL;
	if (i == 0)
		file = ft_strdup("xpm/AmongUs/1.xpm");
	else if (i == 1)
		file = ft_strdup("xpm/AmongUs/2.xpm");
	else if (i == 2)
		file = ft_strdup("xpm/AmongUs/3.xpm");
	else if (i == 3)
		file = ft_strdup("xpm/AmongUs/4.xpm");
	return (file);
}

void	show_loading(t_rt *v)
{
	int		i;
	int		h;
	int		w;
	char	*file;

	i = 0;
	while (i < 4)
	{
		file = get_file_path(i);
		v->m.img_ptr = mlx_xpm_file_to_image(v->m.mlx_ptr, file,
									&w, &h);
		v->m.img_data = (unsigned char *)mlx_get_data_addr(
						v->m.img_ptr, &v->m.bpp, &v->m.size_l, &v->m.endian);
		mlx_put_image_to_window(v->m.mlx_ptr, v->m.win_ptr, v->m.img_ptr,
				0, 0);
		i++;
		mlx_do_sync(v->m.mlx_ptr);
		usleep(450000);
		free(file);
	}
}