/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 06:38:06 by hastid            #+#    #+#             */
/*   Updated: 2020/11/09 01:51:52 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_RT_H
#define STRUCT_RT_H

typedef struct s_vect
{
	double x;
	double y;
	double z;
} t_vect;

typedef struct	s_cordin
{
	int	x;
	int	y;
	int	z;
}				t_cordin;

typedef struct	s_delt
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t;
	double	t1;
	double	t2;
	t_vect	v;
}				t_delt;

typedef struct	s_perlin
{
	int			a;
	int			aa;
	int			ab;
	int			b;
	int			ba;
	int			bb;
}				t_perlin;

typedef struct	s_inter
{
	t_vect		obj_center;
	t_vect		pt;
	double		inter;
	double		nor_dir;
	double		height;
	double		width;
	double		proj1;
	double		proj2;

}				t_inter;

typedef struct	s_texture
{

	int		t;
	int		*buf;
	void	*img;
	double	Um;
	double	Vm;
	int		width;
	int		height;
} t_texture;

typedef struct s_mlx
{
	int bpp;
	int size_l;
	int endian;
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	unsigned char *img_data;
} t_mlx;

typedef struct s_ray
{
	t_vect ori;
	t_vect dir;
	double time;
} t_ray;

typedef struct	s_sc
{
	int		opt;
	int		fil;
	int		aal;
	int		cef;
	double	amb;
}				t_sc;

typedef struct s_cam
{
	int opt;
	t_vect x;
	t_vect y;
	t_vect z;
	double i;
	double j;
	double fov;
	double width;
	double height;
	t_vect ori;
	t_vect tar;
} t_cam;

typedef struct s_obj
{
	int id;
	int opt;
	int neg;
	int trs;
	int rfl;
	int slc;
	int uod;
	int dsp;
	t_vect	e1;
	t_vect	e2;
	double ray;
	t_vect ori;
	t_vect col;
	t_vect axi;
	t_vect tra;
	t_vect rot;
	t_vect lim;
	double width;
	double height;
	double nbr_t;
	double t_max;
	t_texture 	txt;
	struct s_obj *next;
} t_obj;

typedef struct s_light
{
	int id;
	int opt;
	double pow;
	t_vect ori;
	t_vect col;
	t_vect axi;
	double ang;
	struct s_light *next;
} t_light;

typedef struct s_plight
{
	t_vect amb;
	t_vect def;
	t_vect spc;
	double light;
} t_plight;

typedef struct s_point
{
	t_obj *obj;
	t_vect p_dir;
	t_vect p_inter;
	t_vect p_normal;
	t_vect p_color;
	t_plight p_light;
	double inter_min;
} t_point;

typedef struct s_event
{
	char *file;
	char *file_origin;
	int	move_z;
	int	move_x;
	int	rot_y;
	int	rot_x;
} t_event;

typedef struct s_thread
{
	int start;
	int end;
	t_ray ray;
	t_vect color;
} t_thread;

typedef struct s_rt
{
	int id;
	t_sc	s;
	t_mlx	m;
	t_cam	*c;
	t_obj	*o;
	t_light	*l;
	t_point point;
	t_event event;
	t_thread thread;
} t_rt;



#endif
