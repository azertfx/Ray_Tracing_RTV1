/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:37:58 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/04 00:50:03 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int argc, char **argv)
{
	t_rt	v;

	if (argc == 2)
	{
		if (!rt(&v, argv[1]))
			return (1);
	}
	else
		ft_putendl("Usage : ./rt [Scene Path]");
	return (0);
}
