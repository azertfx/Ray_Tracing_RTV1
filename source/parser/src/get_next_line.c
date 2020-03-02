/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:28:51 by llachgar          #+#    #+#             */
/*   Updated: 2020/03/01 04:32:34 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char			*ft_strjoin_f(char *s1, char *s2, int a, int b)
{
	char	*str;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_strcpy(str, (char *)s1);
	ft_strcat(str, (char *)s2);
	if (a)
		free(s1);
	if (b)
		free(s2);
	return (str);
}

static int		get_the_line(char **s, char **line, int fd)
{
	int		len;
	char	*tmp;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = s[fd];
		s[fd] = ft_strdup(s[fd] + len + 1);
		free(tmp);
	}
	else if (s[fd][len] == '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*s[256];
	char		buf[BUFF_SIZE + 1];
	int			r_res;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((r_res = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r_res] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		s[fd] = ft_strjoin_f(s[fd], buf, 1, 0);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (r_res < 0)
		return (-1);
	else if (r_res == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
	{
		if (s[fd])
			free(s[fd]);
		return (0);
	}
	return (get_the_line(s, line, fd));
}
