/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:50:50 by vprypesh          #+#    #+#             */
/*   Updated: 2018/12/03 18:50:51 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*submit_cone(t_object *cone, t_p3d l, t_p3d n)
{
	cone->type = CONE;
	cone->cone = init_cone(l, n, l.len);
	cone->origin = l;
	cone->normal = n;
	cone->intersect = &intersect_cone;
	cone->next = NULL;
	return (cone);
}

void		calc_cone(t_env *env, char **str, Uint32 idx)
{
	t_object	*cone;
	t_p3d		l;
	t_p3d		n;
	Uint32		i;

	i = -1;
	cone = malloc(sizeof(t_object));
	while (str[idx][++i] != '\0')
	{
		if (str[idx][0] != '!')
		{
			free(cone);
			return ;
		}
		if (str[idx][i] == ':' && ft_strncmp(str[idx], "!vertex:", i + 1) == 0)
			l = get_coords(&str[idx][i]);
		if (str[idx + 1][i] == ':'
						&& ft_strncmp(str[idx + 1], "!axis:", i + 1) == 0)
			n = get_coords(&str[idx + 1][i]);
	}
	cone->color = get_color(str, idx + 2);
	cone = submit_cone(cone, l, n);
	push_object(env, cone);
}

t_cone		init_cone(t_p3d vertex, t_p3d axis, double angle)
{
	t_cone cone;

	cone.vertex = vertex;
	cone.axis = v_norm(axis);
	cone.angle = tan(angle / 2);
	return (cone);
}

double		intersect_cone(void *cone, t_ray *ray)
{
	t_cone		*c;
	double		b;
	double		t;
	double		fc;
	double		m;

	c = (t_cone *)cone;
	b = 2 * ((dot_product(ray->dir, vsub(ray->origin, c->vertex))
	- (1 + pow(c->angle, 2))
	* (dot_product(ray->dir, c->axis)
	* dot_product(vsub(ray->origin, c->vertex), c->axis))));
	fc = dot_product(vsub(ray->origin, c->vertex), vsub(ray->origin, c->vertex))
	- (1 + pow(c->angle, 2))
	* pow(dot_product(vsub(ray->origin, c->vertex), c->axis), 2);
	t = quadr_eq(
	dot_product(ray->dir, ray->dir) - (1 + pow(c->angle, 2))
	* pow(dot_product(ray->dir, c->axis), 2), b, fc);
	m = dot_product(ray->dir, c->axis) * t
	+ dot_product(vsub(ray->origin, c->vertex), c->axis);
	c->normal = vsub(vadd(ray->origin, vmult(ray->dir, t)),
	vadd(c->vertex, vmult(c->axis, m)));
	c->normal = v_norm(vsub(c->normal,
	vmult(c->axis, (m * c->angle * c->angle))));
	return (t);
}
