/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:19:20 by hastid            #+#    #+#             */
/*   Updated: 2020/11/09 00:53:45 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdio.h>

# include "rt.h"
# include "libft.h"
# include "struct_rt.h"

# define P_COUNT 11
# define ORI_SET 1
# define TAR_SET 1 << 1
# define FOV_SET 1 << 2
# define COL_SET 1 << 3
# define POW_SET 1 << 4
# define RAY_SET 1 << 5
# define AXI_SET 1 << 6
# define TRA_SET 1 << 7
# define ROT_SET 1 << 8
# define LIGHT_T 1 << 9
# define WID_SET 1 << 10
# define HEI_SET 1 << 11
# define NEG_SET 1 << 12
# define REF_SET 1 << 13
# define TCP_SET 1 << 14
# define AMB_SET 1 << 15
# define FIL_SET 1 << 16
# define AAL_SET 1 << 17
# define CAE_SET 1 << 18
# define DOF_SET 1 << 19
# define ANG_SET 1 << 20
# define SLC_SET 1 << 21
# define UOD_SET 1 << 22
# define LIM_SET 1 << 23
# define DSP_SET 1 << 24
# define LM1_SET 1 << 25
# define LM2_SET 1 << 26
# define MBL_SET 1 << 27
# define TXT_SET 1 << 28

# define IS_SET(apts, apt) (apts & apt)
# define V_COLOR(a) (a >= 0 && a <= 255)

# define BUFF_SIZE 100

enum {ERROR, SUCCESS};
enum {POINT, DIRECT, PARALLEL};
enum {NOTING, COLOR, ROTAT, DIST, ANGL};
enum {NONE, SEPIA, BLACK_WHITE, NEGATIVE, STEREO};
enum {LIGHT, CAMERA, CONE, PLANE, SPHERE, CYLINDER, PARABOL, DISC, SQUARE ,HEMIS, SCENE};
enum {CHECKBOARD, XOR, WOOD, PERLIN};

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

int				parse_scene(t_rt *r, char **tab);
int				parse_camera(t_rt *r, char **tab);
int				parse_lights(t_rt *r, char **tab);
int				parse_objects(t_rt *r, char **tab);

int				get_int(int *p, char *v, int t);
int				get_double(double *p, char *v, int t);
int				get_vector(t_vect *v, char *s, int t);
int				get_next_line(const int fd, char **line);

int				data_is_valid(t_rt *r);

int				add_ray(t_rt *r, char *v);
int				add_axis(t_rt *r, char *v);
int				add_power(t_rt *r, char *v);
int				add_color(t_rt *r, char *v);
int				add_origin(t_rt *r, char *v);

int				add_child(t_rt *r, char **tab);
int				parse_parent(char *line, t_rt *r);

int				parse_file(char *file, t_rt *r);

int				free_rt(t_rt *r);
int				free_tab(char **t, int ret);

#endif
