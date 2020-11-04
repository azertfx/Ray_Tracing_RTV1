#include <stdio.h>
#include <math.h>

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

void show_vect(t_vect v)
{
    printf( " v = | %.2lf,%.2lf,%.2lf | ", v.x, v.y, v.z);
}

t_vect		rotate(t_vect v, t_vect r)
{
	t_vect res;

	res.x = v.x;
	res.y = v.y * cos(r.x) + v.z * sin(r.x);
	res.z = -v.y * sin(r.x) + v.z * cos(r.x);
	v = (t_vect) {res.x, res.y, res.z};
	res.x = v.x * cos(r.y) + v.z * sin(r.y);
	res.y = v.y;
	res.z = -v.x * sin(r.y) + v.z * cos(r.y);
	v = (t_vect) {res.x, res.y, res.z};
	res.x = v.x * cos(r.z) - v.y * sin(r.z);
	res.y = v.x * sin(r.z) + v.y * cos(r.z);
	res.z = v.z;
	return (res);
}

int main()
{
    printf("Hello World\n");
    t_vect v = {30,0,0};
    t_vect r = {0,0,60};
    t_vect res = rotate(v, r);
    show_vect(res);
    return 0;
}
