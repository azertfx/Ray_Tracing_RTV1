/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 00:48:32 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/11/16 03:36:22 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

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
# define SPACE 49
# define ORI "Original"
# define OBJ "objects"
# define LGH "lights"
# define LIM "limited_obj"
# define DIS "disruptions"
# define SPL "spot light"
# define RFL "reflection"
# define RFR "refraction"
# define TRSHDW "trs_shadow"
# define TEXTUR "textures"
# define CMPELE "composed_elem"
# define NOISEWIDTH 192
# define NOISEHEIGHT 192
# define NOISEDEPTH 64

double g_noise[NOISEDEPTH][NOISEHEIGHT][NOISEWIDTH];
static int g_p[512];

/*
** Vectors functions
*/
t_vect			ft_vect_mult_nbr(t_vect u, double t);
t_vect			ft_vect_add(t_vect u, t_vect v);
t_vect			ft_vect_mult(t_vect u, t_vect v);
t_vect			ft_vect_add_nbr(t_vect u, double t);
void			ft_vect_init(t_vect *v, double x, double y, double z);
t_vect			ft_vect_cross(t_vect u, t_vect v);
t_vect			ft_vect_norm(t_vect *vec);
double			ft_vect_dot(t_vect u, t_vect v);
double			ft_vect_length(t_vect vec);
t_vect			ft_vect_div_nbr(t_vect u, double t);
double			ft_vect_dist(t_vect u, t_vect v);
t_vect			ft_vect_rotate(t_vect v, t_vect r);
t_vect			*check_vector(char *str);
t_vect			ft_vect_sub(t_vect u, t_vect v);
/*
** Addictional function
*/
double			rad(double x);
double			px_x(double x);
double			px_y(double y);
/*
** Parsing
*/
char			*parse_property(void *obj, char *line, int o_type);
int				check_file(t_rt *v);
/*
** Ray Tracer
*/
t_vect			ray_trace(t_rt *v, t_ray *ray, t_vect *color, t_vect depth);
void			ft_instruction(t_rt *v);
void			ft_draw_btn(t_rt *v, int x, int y);
void			ft_btn_content(t_rt *v);
int				rt(t_rt *v, char *file);
void			draw(t_rt v);
double			intersection_checker(t_rt *v, t_ray r, t_point *point);
void			get_pixel_color(t_rt *v, t_vect *light_color);
void			calculate_pixel_color(t_rt *v, t_light *light);
void			objects_normal(t_ray r, t_point *point);
void			generate_camera_ray(t_rt *v, t_ray *r, double *axis, int a);
void			generate_camera(t_rt *v);
/*
** Objects
*/
double			cone_intersection(t_ray r, t_obj *obj);
double			plane_intersection(t_ray r, t_obj *obj);
double			sphere_intersection(t_ray r, t_obj *obj);
double			cylinder_intersection(t_ray r, t_obj *obj);
double			paraboloid_intersection(t_ray r, t_obj *parab);
double			disc_intersection(t_ray r, t_obj *obj);
double			square_intersection(t_ray r, t_obj *obj);
double			hemisphere_intersection(t_ray r, t_obj *obj);
double			pen_intersection(t_ray r, t_obj *obj);
double			equation_solve(t_ray ray, t_delt d, t_obj *obj);
double			check_solution(double t1, double t2);
/*
** Pixel
*/
void			set_pixel_color(t_rt *v, int i, int j, t_vect color);
void			pixel_ambient(t_rt *v, int i);
void			pixel_diffuse(t_rt *v, t_light *light);
void			pixel_specular(t_rt *v, t_light *light);
void			check_refl_refr(t_rt *v, t_ray *ray, t_vect *depth);
/*
** Mlx - bmp
*/
int				ft_keys_hook(int k, t_rt *v);
int				save_bmp_image(t_mlx image);
void			init_event(t_rt *v, char *file);
void			init_mlx(t_rt *v);
void			show_loading(t_rt *v);
/*
** Noise
*/
void			apply_noise(t_point *p);
void			generate_noise();
void			wood(t_vect pt, t_vect *color, double xy_period);
double			pnoise(double x, double y, double z);
void			perlin(t_vect v, t_vect *color);
/*
** Slice
*/
double			ft_slice(t_ray r, t_obj *obj, double t);
/*
** Filters
*/
void			filters(t_vect *color, int filter);
double			spotlight(t_vect p, t_light light, double cos_angle);
void			anti_aliasing(t_rt *v, t_ray *r, double *axis, int a);
void			motion_blur(t_ray *r, int a);
/*
** Texture
*/
int				add_texture(t_rt *rt);
void			get_angle(t_obj *obj, t_vect inter);
int				color_texture(t_point *point);

double			negative_objects(double t_min, t_ray r, double t_max, t_rt *rt);

int				exit_err(t_rt *r);

#endif
