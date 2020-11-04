/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <hhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 00:48:32 by hhamdaou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/11/04 04:59:24 by hhamdaou         ###   ########.fr       */
=======
/*   Updated: 2020/11/04 04:29:35 by hezzahir         ###   ########.fr       */
>>>>>>> 7d1273c2d15007ede20b07851d15f8fd41e0fb09
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
# define noiseWidth 192
# define noiseHeight 192
# define noiseDepth 64
# define RAD(x) (x * M_PI / 180)
# define PX_X(x) ((x + 0.5) * 2.0 / (double)IMG_W - 1.0)
# define PX_Y(y) (1.0 - (y + 0.5) * 2.0 / (double)IMG_H)

double noise[noiseDepth][noiseHeight][noiseWidth];

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
void			calculate_pixel_color(t_rt *v, t_light *light, int i);
void			objects_normal(t_ray r, t_point *point);
void			generate_camera_ray(t_rt *v, t_ray *r, double *axis, int a);
void			generate_camera(t_rt *v);
/*
** Objects
*/
double			sphere_intersection(t_ray r, t_obj *obj);
double			cylinder_intersection(t_ray r, t_obj *obj);
double			plane_intersection(t_ray r, t_obj *obj);
double			cone_intersection(t_ray r, t_obj *obj);
double			equation_solve(t_ray ray,t_delt d, t_obj *obj);
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

/*
** Noise
*/
void			apply_noise(t_point *p);
void			generate_noise();
void			wood(t_vect pt, t_vect *color);
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
void			GetAngle(t_obj *obj , t_vect inter);
int				getColorFromTexture(t_point *point);
<<<<<<< HEAD
void			filters(t_vect *color, int filter);
void			generate_noise();
void			wood(t_vect pt, t_vect *color);
double			equation_solve(t_ray ray,t_delt d, t_obj *obj);
double			check_solution(double t1, double t2);
void	check_refl_refr(t_rt *v, t_ray *ray, t_vect *depth);
void	set_pixel_color(t_rt *v, int i, int j, t_vect color);
void		pixel_ambient(t_rt *v, int i);
void		pixel_diffuse(t_rt *v, t_light *light);
void		pixel_specular(t_rt *v, t_light *light);
double		spotlight(t_vect p, t_light light, double cos_angle);
void	anti_aliasing(t_rt *v, t_ray *r, double *axis, int a);
void	motion_blur(t_ray *r, int a);
void    init_event(t_rt *v, char *file);
void    init_mlx(t_rt *v);

=======
>>>>>>> 7d1273c2d15007ede20b07851d15f8fd41e0fb09
#endif
