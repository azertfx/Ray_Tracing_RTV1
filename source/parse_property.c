/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_property.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 00:10:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/02/29 00:52:56 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	*get_obj_property(t_obj *obj, char *property, int *p_type)
{
	if (ft_strequ(property, "origin") && (*p_type = 1))
		return (&obj->ori);
	else if (ft_strequ(property, "color") && (*p_type = 1))
		return (&obj->col);
	if (ft_strequ(property, "axis") && (*p_type = 1))
		return (&obj->axi);
	else if (ft_strequ(property, "translation") && (*p_type = 1))
		return (&obj->tra);
	if (ft_strequ(property, "rotation") && (*p_type = 1))
		return (&obj->rot);
	else if (ft_strequ(property, "ray") && (*p_type = 2))
		return (&obj->ray);
	return (NULL);
}

static void	*get_light_property(t_light *light, char *property, int *p_type)
{
	if (ft_strequ(property, "origin") && (*p_type = 1))
		return (&light->ori);
	else if (ft_strequ(property, "color") && (*p_type = 1))
		return (&light->col);
	else if (ft_strequ(property, "power") && (*p_type = 2))
		return (&light->pow);
	return (NULL);
}

static void	*get_cam_property(t_cam *cam, char *property, int *p_type)
{
	if (ft_strequ(property, "origin") && (*p_type = 1))
		return (&cam->ori);
	else if (ft_strequ(property, "target") && (*p_type = 1))
		return (&cam->tar);
	else if (ft_strequ(property, "fov") && (*p_type = 2))
		return (&cam->fov);
	return (NULL);
}

static char	*parse_vector(t_vect *vec, char *line)
{
	vec->x = ft_atof(line);
	ft_strchr("+-", *line) ? line++ : 0;
	if ((line = ft_skip_chars(line, ".", ft_isdigit)) && *line++ != ',')
		return (NULL);
	vec->y = ft_atof(line);
	ft_strchr("+-", *line) ? line++ : 0;
	if ((line = ft_skip_chars(line, ".", ft_isdigit)) && *line++ != ',')
		return (NULL);
	vec->z = ft_atof(line);
	ft_strchr("+-", *line) ? line++ : 0;
	return (ft_skip_chars(line, ".", ft_isdigit));
}

char		*parse_property(void *obj, char *line, int o_type)
{
	int		p_type;
	void	*prop;

	o_type == 0 ? (prop = get_cam_property(obj, line, &p_type)) : 0;
	o_type == 1 ? (prop = get_light_property(obj, line, &p_type)) : 0;
	o_type == 2 ? (prop = get_obj_property(obj, line, &p_type)) : 0;
	line = ft_skip_chars(line + ft_strlen(line) + 1, " ", NULL);
	if (!prop)
		return (NULL);
	if (p_type == 1)
		return (parse_vector(prop, line));
	*((double *)prop) = ft_atof(line);
	ft_strchr("+-", *line) ? line++ : 0;
	return (ft_skip_chars(line, ".", ft_isdigit));
}
