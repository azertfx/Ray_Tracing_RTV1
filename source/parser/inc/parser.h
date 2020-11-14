/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:19:20 by hastid            #+#    #+#             */
/*   Updated: 2020/11/14 03:21:37 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdio.h>

# include "rt.h"
# include "libft.h"
# include "struct_rt.h"

# define P_COUNT 12
# define BUFF_SIZE 100

enum {ERROR, SUCCESS};
enum {POINT, DIRECT, PARALLEL};
enum {NOTING, COLOR, ROTAT, DIST, ANGL};
enum {NONE, SEPIA, BLACK_WHITE, NEGATIVE, STEREO};
enum {LIGHT, CAMERA, CONE, PLA, SPH, CYL, PARA, DISC, SQUAR, HEMIS, PEN, SCENE};
enum {CHECKBOARD, XOR, WOOD, PERLIN, WHITE_BLACK};

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

int				g_ori;
int				g_tar;
int				g_fov;
int				g_col;
int				g_pow;
int				g_ray;
int				g_axi;
int				g_tra;
int				g_rot;
int				g_lgt;
int				g_wid;
int				g_hei;
int				g_neg;
int				g_ref;
int				g_tcp;
int				g_amb;
int				g_fil;
int				g_aal;
int				g_cae;
int				g_dof;
int				g_ang;
int				g_slc;
int				g_uod;
int				g_lim;
int				g_dsp;
int				g_lmo;
int				g_lmt;
int				g_mbl;
int				g_txt;

void			init_parser(void);
void			init_rt_parser(t_rt *r);
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

int				add_width(t_rt *r, char *v);
int				add_height(t_rt *r, char *v);
int				add_negative(t_rt *r, char *v);
int				add_rotation(t_rt *r, char *v);
int				add_reflection(t_rt *r, char *v);
int				add_translation(t_rt *r, char *v);
int				add_transparence(t_rt *r, char *v);
int				add_slice(t_rt *r, char *v);
int				add_limit(t_rt *r, char *v);
int				add_upordown(t_rt *r, char *v);

int				add_filters(t_rt *r, char *v);

int				is_set(int opts, int opt);

#endif
