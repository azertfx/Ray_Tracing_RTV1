/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:19:20 by hastid            #+#    #+#             */
/*   Updated: 2020/03/04 04:39:47 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdio.h>

# include "libft.h"
# include "struct_rt.h"

# define P_COUNT 6
# define CAMERA_C_C 3
# define SPHERE_C_C 3
# define LIGHT_C_C 3
# define ORI_SET 1
# define TAR_SET 1 << 1
# define FOV_SET 1 << 2
# define COL_SET 1 << 3
# define POW_SET 1 << 4
# define RAY_SET 1 << 5
# define AXI_SET 1 << 6
# define TRA_SET 1 << 7
# define ROT_SET 1 << 8
# define IS_SET(apts, apt) (apts & apt)
# define V_COLOR(a) (a >= 0 && a <= 255)

# define BUFF_SIZE 100

enum {ERROR, SUCCESS};
enum {LIGHT, CAMERA, CONE, PLANE, SPHERE, CYLINDER};
enum {ORIGIN, COLOR, POWER, RAY, FOV, AXIS, TRANS, ROTAT};

typedef struct	s_parent
{
	char		*p;
	int			(*f)(t_rt *r);
}				t_parent;

typedef struct	s_child
{
	char		*name;
	int			(*f)(t_rt *r, char *l);
}				t_child;

int				get_int(int *p, char *v, int t);
int				get_double(double *p, char *v, int t);
int				get_vect(t_vect *v, char *s, int t);
int				get_next_line(const int fd, char **line);

int				data_is_valid(t_rt *r);

int				add_ray(t_rt *r, char *v);
int				add_fov(t_rt *r, char *v);
int				add_power(t_rt *r, char *v);
int				add_origin(t_rt *r, char *v);
int				add_target(t_rt *r, char *v);

int				add_child(t_rt *r, char *l);
int				parse_parent(char *line, t_rt *r);

int				parse_file(char *file, t_rt *r);

#endif
