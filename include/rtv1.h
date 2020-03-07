/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:17:11 by anabaoui          #+#    #+#             */
/*   Updated: 2020/03/07 02:19:08 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <pthread.h>
# include "../miniLibX/mlx.h"

# include "libft.h"
# include "parser.h"
# include "struct_rt.h"
# include "bmp.h"

# define IMG_H 700
# define IMG_W 700
# define WIN_W 910
# define MIN_NBR 1e-4
# define MAX_NBR 1e8
# define THREADS 4
# define O 31
# define S 1
# define X 7
# define Y 16
# define Z 6
# define Q 12
# define W 13
# define P 35
# define L 37
# define R 15
# define T 17
# define ESC 53
# define ESPACE 49
# define ORI "Original"
# define SPH "sphere"
# define PLA "plane"
# define CON "cone"
# define CYL "cylinder"
# define TRA "translation"
# define ROT "rotation"
# define CAM "camera_y"
# define MULTIS "multi_spots"
# define MULTI1 "multi_objs_1"
# define MULTI2 "multi_objs_2"

# define RAD(x) (x * M_PI / 180)
# define PX_X(x) ((x + 0.5) * 2.0 / (double)IMG_W - 1.0)
# define PX_Y(y) (1.0 - (y + 0.5) * 2.0 / (double)IMG_H)

char			*parse_property(void *obj, char *line, int o_type);
int				check_file(t_rt *v);
void			ft_instruction(t_rt *v);
void			ft_draw_btn(t_rt *v, int x, int y);
void			ft_btn_content(t_rt *v);
int				rtv1(t_rt *v, char *file);
void			draw(t_rt v);
double			intersection_checker(t_rt *v, t_ray r, t_point *point);
void			calculate_pixel_color(t_rt *v, t_light *light, int i);
t_vect		    ray_trace(t_rt *v, t_ray *ray, t_vect *color);
void			get_pixel_color(t_rt *v, t_vect *light_color);
void			objects_normal(t_ray r, t_point *point);
void			generate_camera_ray(t_rt *v, t_ray *r, double y, double x);
void			generate_camera(t_rt *v);
double			sphere_intersection(t_ray r, t_obj *obj);
double			cylinder_intersection(t_ray r, t_obj *obj);
double			plane_intersection(t_ray r, t_obj *obj);
double			cone_intersection(t_ray r, t_obj *obj);
t_vect	    	*check_vector(char *str);
t_vect	    	ft_vect_sub(t_vect u, t_vect v);
t_vect	    	ft_vect_mult_nbr(t_vect u, double t);
t_vect	    	ft_vect_add(t_vect u, t_vect v);
t_vect	    	ft_vect_mult(t_vect u, t_vect v);
t_vect	    	ft_vect_add_nbr(t_vect u, double t);
void			ft_vect_init(t_vect *v, double x, double y, double z);
t_vect	    	ft_vect_cross(t_vect u, t_vect v);
t_vect	    	ft_vect_norm(t_vect *vec);
double			ft_vect_dot(t_vect u, t_vect v);
double			ft_vect_length(t_vect vec);
t_vect		    ft_vect_div_nbr(t_vect u, double t);
double			ft_vect_dist(t_vect u, t_vect v);
t_vect		    ft_vect_rotate(t_vect v, t_vect r);
int				ft_keys_hook(int k, t_rt *v);
int				save_bmp_image(t_mlx image);
#endif
