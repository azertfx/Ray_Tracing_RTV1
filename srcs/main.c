/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:37:58 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/27 23:38:13 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int argc, char **argv)
{
	t_var	v;

	if (argc == 2)
	{
		if (!rtv1(&v, argv[1]))
			return (1);
	}
	else
		ft_putendl("Usage : ./rtv1 [Scene Path]");
	return (0);
}
