/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:37:58 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/03 00:13:30 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int argc, char **argv)
{
	t_rt	v;

	if (argc == 2)
	{
		if (!rtv1(&v, argv[1]))
			return (1);
	}
	else
		ft_putendl("Usage : ./rt [Scene Path]");
	return (0);
}
