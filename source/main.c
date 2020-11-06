/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:37:58 by anabaoui          #+#    #+#             */
/*   Updated: 2020/11/05 23:16:43 by hezzahir         ###   ########.fr       */
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
