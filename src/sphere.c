/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:38:46 by vprypesh          #+#    #+#             */
/*   Updated: 2018/06/21 16:38:46 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*submit_sphere(t_object *new_sphere, t_p3d s, Uint32 color)
{
	new_sphere->type = SPHERE;
	new_sphere->sphere = init_sphere(s, s.len, color);
	new_sphere->intersect = &intersect_sphere;
	new_sphere->color = color;
	new_sphere->origin = s;
	new_sphere->radius = s.len;
	new_sphere->next = NULL;
	return (new_sphere);
}

Uint32		calc_sphere(t_env *env, char **str, Uint32 idx)
{
	t_object	*new_sphere;
	t_p3d		s;
	Uint32		color;
	Uint32		i;

	i = 0;
	new_sphere = malloc(sizeof(t_object));
	while (str[idx][i])
	{
		if (str[idx][0] != '!')
		{
			free(new_sphere);
			return (0);
		}
		if (str[idx][i] == ':' && (ft_strncmp(str[idx], "!coords:", 8) == 0))
			s = get_coords(&str[idx][i]);
		i++;
	}
	color = get_color(str, idx + 1);
	new_sphere = submit_sphere(new_sphere, s, color);
	push_object(env, new_sphere);
	return (1);
}

t_sphere	init_sphere(t_p3d coords, double r, double color)
{
	t_sphere s;

	s.origin.x = coords.x;
	s.origin.y = coords.y;
	s.origin.z = coords.z;
	s.radius = r;
	s.color = color;
	return (s);
}

double		quadr_eq(double a, double b, double c)
{
	double d;
	double t;
	double t1;

	d = b * b - 4 * a * c;
	t = 0;
	if (d > 0)
	{
		t = (-b + sqrt(d)) / (2 * a);
		t1 = (-b - sqrt(d)) / (2 * a);
		(t > t1 && t1 > 0) ? t = t1 : 0;
	}
	return (t);
}

double		intersect_sphere(void *s, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		t;
	t_sphere	*sp;

	sp = (t_sphere *)s;
	a = dot_product(ray->dir, ray->dir);
	b = dot_product(ray->dir, vsub(ray->origin, sp->origin)) * 2;
	c = dot_product(vsub(ray->origin, sp->origin),
	vsub(ray->origin, sp->origin)) - (sp->radius * sp->radius);
	t = quadr_eq(a, b, c);
	sp->normal = v_norm(vsub(vadd(ray->origin,
						vmult(ray->dir, t)), sp->origin));
	return (t);
}
