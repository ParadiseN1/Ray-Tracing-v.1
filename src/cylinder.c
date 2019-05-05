/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:50:50 by vprypesh          #+#    #+#             */
/*   Updated: 2018/12/03 18:50:51 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object		*submit_cylinder(t_object *cyl, t_p3d l, t_p3d n, double len)
{
	cyl->type = CYLINDER;
	cyl->cylinder = init_cylinder(l, n, len, l.len);
	cyl->origin = l;
	cyl->normal = n;
	cyl->intersect = &intersect_cylinder;
	cyl->next = NULL;
	return (cyl);
}

void			calc_cylinder(t_env *env, char **s, int i)
{
	t_object	*cylinder;
	t_p3d		l;
	t_p3d		n;
	Uint32		j;
	double		length;

	j = -1;
	cylinder = malloc(sizeof(t_object));
	while (s[i][++j] != '\0')
	{
		if (s[i][0] != '!')
		{
			free(cylinder);
			return ;
		}
		if (s[i][j] == ':' && ft_strncmp(s[i], "!coords:", j + 1) == 0)
			l = get_coords(&s[i][j]);
		if (s[i + 1][j] == ':' && ft_strncmp(s[i + 1], "!axis:", j + 1) == 0)
			n = get_coords(&s[i + 1][j]);
		if (s[i + 2][j] == ':' && ft_strncmp(s[i + 2], "!length:", j + 1) == 0)
			length = float_atoi(&s[i + 2][j + 1]);
	}
	cylinder->color = get_color(s, i + 3);
	cylinder = submit_cylinder(cylinder, l, n, length);
	push_object(env, cylinder);
}

t_cylinder		init_cylinder(t_p3d o, t_p3d axis, double length, double radius)
{
	t_cylinder cylinder;

	cylinder.origin = o;
	cylinder.axis = v_norm(axis);
	cylinder.length = length;
	cylinder.radius = radius;
	cylinder.end = vadd(o, vmult(v_norm(axis), length));
	return (cylinder);
}

double			intersect_cylinder(void *cylinder, t_ray *ray)
{
	t_cylinder	*c;
	double		a;
	double		b;
	double		fc;
	double		t;

	c = (t_cylinder *)cylinder;
	a = dot_product(ray->dir, ray->dir)
	- pow(dot_product(ray->dir, c->axis), 2);
	b = 2 * (dot_product(ray->dir, vsub(ray->origin, c->origin))
	- (dot_product(ray->dir, c->axis) * dot_product(
		vsub(ray->origin, c->origin), c->axis)));
	fc = dot_product(vsub(ray->origin, c->origin), vsub(ray->origin, c->origin))
	- pow(dot_product(vsub(ray->origin, c->origin),
					c->axis), 2) - pow(c->radius, 2);
	t = quadr_eq(a, b, fc);
	c->normal = v_norm(vsub(vadd(ray->origin, vmult(ray->dir, t)),
	vadd(c->origin, vmult(c->axis,
	dot_product(ray->dir, c->axis) * t
	+ dot_product(vsub(ray->origin, c->origin), c->axis)))));
	return (t);
}
