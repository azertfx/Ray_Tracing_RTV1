#include "rt.h"

typedef struct		s_repere
{
	t_vect				i;
	t_vect				j;
	t_vect				k;
}					t_repere;

int		equal(t_vect vect1, t_vect vect2)
{
	if (vect1.y == vect2.y)
		return (1);
	if (vect1.y == -vect2.y)
		return (2);
	return (0);
}

t_vect	constrector(double x, double y, double z)
{
	t_vect vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}


t_repere set_repere(t_vect dir)
{
    t_repere rep;
    t_vect up;

    up = constrector(0.0, 1.0, 0.0);
    rep.j = dir;
	if (equal(up, rep.j) == 1)
	{
		rep.i = constrector(1.0, 0.0, 0.0);
		rep.k = constrector(0.0, 0.0, 1.0);
	}
	else
	{
		if (equal(up, rep.j) == 2)
		{
			rep.i = constrector(-1.0, 0.0, 0.0);
			rep.k = constrector(0.0, 0.0, 1.0);
		}
		else
		{
			rep.i = ft_vect_cross(up, rep.j);
			rep.k = ft_vect_cross(rep.i, rep.j);
		}
	}
    return (rep);
}

int			add_texture(t_rt *rt)
{
	t_obj *temp;

	temp = rt->o;
	while(temp)
	{
        if (temp->txt.t)
        {
            temp->txt.img = mlx_xpm_file_to_image(rt->m.mlx_ptr, "xpm/earth.xpm", &temp->txt.width,&temp->txt.height);
            if (!temp->txt.img)
                return (0);
            temp->txt.buf = (int *)mlx_get_data_addr(temp->txt.img, &rt->m.bpp,&rt->m.size_l, &rt->m.endian);
        }
		temp = temp->next;
	}
	return (1);
}


int GetPlan(t_obj *plane_temp , t_vect p)
{
	plane_temp->txt.Um = p.x * 0.01;
	plane_temp->txt.Vm = p.y * 0.01;
	plane_temp->txt.Um -= floor(plane_temp->txt.Um);
	plane_temp->txt.Vm -= floor(plane_temp->txt.Vm);
	return (1);
}

int 	GetSphere(t_obj *sphere_temp , t_vect p)
{
	double phi;
	double theta;

    phi = atan2(p.z, p.x);
	theta = asin(p.y / sphere_temp->ray) ;
	sphere_temp->txt.Um = 1 - (phi + M_PI) / (2.0 * M_PI);
    sphere_temp->txt.Vm = (theta + M_PI / 2.0) / M_PI;
	return (1);
}

int GetCylinder(t_obj *plane_temp , t_vect p)
{
	plane_temp->txt.Um = (atan2(p.x, p.z) / (2.0 * M_PI));
	plane_temp->txt.Vm = (p.y + 4.0 /2 )/ 4.0;
	plane_temp->txt.Um -= floor(plane_temp->txt.Um);
	plane_temp->txt.Vm -= floor(plane_temp->txt.Vm);
	return (1);
}

int GetCone(t_obj *cone_temp, t_vect p)
{
	cone_temp->txt.Um = (atan2(p.x, p.z) / (2.0 * M_PI));
	cone_temp->txt.Vm = (p.y + 5.0 /2 )/ 5.0;
	cone_temp->txt.Um -= floor(cone_temp->txt.Um);
	cone_temp->txt.Vm -= floor(cone_temp->txt.Vm);
	return (1);
}

void   Get(t_obj *obj , t_vect inter)
{
	if(obj->id == SPHERE)
		GetSphere(obj , inter);
	else if (obj->id  == PLANE)
		GetPlan(obj , inter);
	else if (obj->id  == CYLINDER)
		GetCylinder(obj , inter);
	else if (obj->id  == CONE)
		GetCone(obj , inter);
}

int		getColorFromTexture(t_point *point)
{
	int		i;
	int		j;
	t_vect  p;
	// t_vect	inter;
	t_repere rep;

	rep = set_repere(constrector(0.0, 1.0, 0.0));
	p = ft_vect_sub(point->obj->ori,constrector(ft_vect_dot(point->p_inter,rep.i), ft_vect_dot(point->p_inter, rep.j), ft_vect_dot(point->p_inter, rep.k)));
    // p = constrector(ft_vect_dot(point->p_inter,rep.i), ft_vect_dot(point->p_inter, rep.j), ft_vect_dot(point->p_inter, rep.k));
    Get(point->obj, p);
    i = point->obj->txt.Um * point->obj->txt.width;
    j = (1.0 - point->obj->txt.Vm) * point->obj->txt.height - 0.001;
    i = (i < 0) ? 0 : i;
    j = (j < 0) ? 0 : j;
    i = (i > point->obj->txt.width - 1) ? point->obj->txt.width - 1 : i;
    j = (j > point->obj->txt.height - 1) ? point->obj->txt.height - 1 : j;
    if (point->obj->txt.buf[j * point->obj->txt.width + i] == -16777216)
            return (0);
    point->p_color.x = (point->obj->txt.buf[j * point->obj->txt.width + i] >> 16) & 0xFF;
    point->p_color.y = (point->obj->txt.buf[j * point->obj->txt.width + i] >> 8) & 0xFF;
    point->p_color.z = point->obj->txt.buf[j * point->obj->txt.width + i] & 0xFF;
	return (1);
}
