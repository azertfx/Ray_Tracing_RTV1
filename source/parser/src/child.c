/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:18:26 by hastid            #+#    #+#             */
/*   Updated: 2020/11/06 02:29:32 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_child(t_rt *r, char **tab)
{
	if (!tab[1])
		return (free_tab(tab, ERROR));
	if (r->id == CAMERA)
		return (parse_camera(r, tab));
	else if (r->id == SCENE)
		return (parse_scene(r, tab));
	else if (r->id == LIGHT)
		return (parse_lights(r, tab));
	else
		return (parse_objects(r, tab));
	return (free_tab(tab, ERROR));
}
