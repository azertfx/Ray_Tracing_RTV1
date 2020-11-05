/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:33:28 by hastid            #+#    #+#             */
/*   Updated: 2020/11/05 23:21:58 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int free_rt(t_rt *r)
{
	t_obj *tmp_o;
	t_light *tmp_l;

	if (r->c)
		ft_memdel((void **)&(r->c->tar));
	if (r->o)
	{
		while (r->o)
		{
			tmp_o = r->o->next;
			ft_memdel((void **)&(r->o));
			r->o = tmp_o;
		}
	}
	if (r->l)
	{
		while (r->l)
		{
			tmp_l = r->l->next;
			ft_memdel((void **)&(r->l));
			r->l = tmp_l;
		}
	}
	return (0);
}

int parse_line(char *line, t_rt *r)
{
	char **tab;

	if (line[0] == '\t')
	{
		if ((tab = ft_strsplit(&line[1], ' ')))
			return (add_child(r, tab));
	}
	return (parse_parent(line, r));
}

int is_ignored(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '\0' || str[i] == '#')
		return (1);
	return (0);
}

int parse_err(t_rt *r, char *line)
{
	free_rt(r);
	ft_putstr_fd("PARSE ERROR\n", 2);
	if (line)
		ft_memdel((void **)&line);
	exit(1);
	return (ERROR);
}

int parse_file(char *file, t_rt *r)
{
	int fd;
	char *line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERROR);
	r->c = 0;
	r->o = 0;
	r->l = 0;
	r->id = -1;
	r->s.amb = 80;
	line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!line)
			break;
		if (is_ignored(line))
			continue;
		if (!parse_line(line, r))
			parse_err(r, line);
		ft_strdel(&line);
	}
	if (data_is_valid(r))
		return (SUCCESS);
	parse_err(r, 0);
	return (ERROR);
}
