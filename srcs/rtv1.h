/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anabaoui <anabaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:17:11 by anabaoui          #+#    #+#             */
/*   Updated: 2020/02/29 02:55:28 by anabaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# include <pthread.h>

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
# define ORI "Original"
# define SPHERE "sphere"
# define PLANE "plane"
# define CONE "cone"
# define CYLINDR "cylinder"
# define TRANS "translation"
# define ROT "rotation"
# define CAMERA "camera_y"
# define MULTIS "multi_spots"
# define MULTI1 "multi_objs_1"
# define MULTI2 "multi_objs_2"

typedef struct	s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned char	*img_data;
	int				bpp;
	int				size_l;
	int				endian;
}				t_mlx;

typedef	struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_obj
{
	t_vector		o;
	t_vector		color;
	t_vector		axis;
	t_vector		trans;
	t_vector		rot;
	double			id;
	double			r;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_light
{
	t_vector		o;
	t_vector		color;
	double			power;
	struct s_light	*next;
}				t_light;

typedef struct	s_cam
{
	t_vector	o;
	t_vector	target;
	t_vector	x;
	t_vector	y;
	t_vector	z;
	double		i;
	double		j;
	double		fov;
	double		height;
	double		width;
}				t_cam;

typedef struct	s_ray
{
	t_vector	o;
	t_vector	dir;

}				t_ray;

typedef struct	s_plight
{
	t_vector	amb;
	t_vector	def;
	t_vector	spc;
	double		light;
}				t_plight;

typedef struct	s_point
{
	t_vector	p_inter;
	t_vector	p_normal;
	t_vector	p_dir;
	t_vector	p_color;
	t_plight	p_light;
	t_obj		*obj;
	double		inter_min;
}				t_point;

typedef struct	s_event
{
	char		*file;
	char		*file_origin;
}				t_event;

typedef struct	s_thread
{
	int				start;
	int				end;
	t_ray			ray;
	t_vector		color;
}				t_thread;

typedef struct	s_var
{
	t_mlx			mlx;
	t_obj			*obj;
	t_light			*light;
	t_cam			*cam;
	t_ray			ray;
	t_point			point;
	t_event			event;
	t_thread		thread;
}				t_var;

void			free_all_object(t_var *v);
int				parse_file(char *file, t_var *v);
char			*parse_property(void *obj, char *line, int o_type);
int				check_file(t_var *v);
void			ft_instruction(t_var *v);
void			ft_draw_btn(t_var *v, int x, int y);
void			ft_btn_content(t_var *v);
int				rtv1(t_var *v, char *file);
void			draw(t_var v);
double			intersection_checker(t_var *v, t_ray r, t_point *point);
void			calculate_pixel_color(t_var *v, t_light *light, int i);
t_vector		ray_trace(t_var *v, t_ray *ray, t_vector *color);
void			get_pixel_color(t_var *v, t_vector *light_color);
void			objects_normal(t_ray r, t_point *point);
void			generate_camera_ray(t_var *v, t_ray *r, double y, double x);
void			generate_camera(t_var *v);
double			sphere_intersection(t_ray r, t_obj *obj);
double			cylinder_intersection(t_ray r, t_obj *obj);
double			plane_intersection(t_ray r, t_obj *obj);
double			cone_intersection(t_ray r, t_obj *obj);
t_vector		*check_vector(char *str);
t_vector		ft_vector_sub(t_vector u, t_vector v);
t_vector		ft_vector_mult_nbr(t_vector u, double t);
t_vector		ft_vector_add(t_vector u, t_vector v);
t_vector		ft_vector_mult(t_vector u, t_vector v);
t_vector		ft_vector_add_nbr(t_vector u, double t);
void			ft_vector_init(t_vector *v, double x, double y, double z);
t_vector		ft_vector_cross(t_vector u, t_vector v);
t_vector		ft_vector_norm(t_vector *vec);
double			ft_vector_dot(t_vector u, t_vector v);
double			ft_vector_length(t_vector vec);
t_vector		ft_vector_div_nbr(t_vector u, double t);
double			ft_vector_dist(t_vector u, t_vector v);
t_vector		ft_vector_rotate(t_vector v, t_vector r);
int				ft_keys_hook(int k, t_var *v);

#endif
