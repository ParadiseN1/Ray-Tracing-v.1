/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:18:11 by vprypesh          #+#    #+#             */
/*   Updated: 2018/07/04 16:18:11 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			next_physical(t_object **obj)
{
	if (*obj == NULL)
		return (1);
	if (((*obj)->type == SPHERE || (*obj)->type == PLANE
	|| (*obj)->type == CONE || (*obj)->type == CYLINDER))
		return (1);
	(*obj) = (*obj)->next;
	return (next_physical(obj));
}

t_object	*submit_plane(t_object *plane, t_p3d l, t_p3d n, Uint32 color)
{
	plane->type = PLANE;
	plane->plane = init_plane(l, n, color);
	plane->origin = l;
	plane->normal = n;
	plane->intersect = &intersect_plane;
	plane->color = color;
	plane->next = NULL;
	return (plane);
}

void		calc_plane(t_env *env, char **str, int idx)
{
	t_object	*plane;
	t_p3d		l;
	t_p3d		n;
	Uint32		i;
	Uint32		color;

	i = 0;
	plane = malloc(sizeof(t_object));
	while (str[idx][i] != '\0')
	{
		if (str[idx][0] != '!')
		{
			free(plane);
			return ;
		}
		if (str[idx][i] == ':' && ft_strncmp(str[idx], "!coords:", i + 1) == 0)
			l = get_coords(&str[idx][i]);
		if (str[idx + 1][i] == ':'
		&& ft_strncmp(str[idx + 1], "!normal:", i + 1) == 0)
			n = get_coords(&str[idx + 1][i]);
		i++;
	}
	color = get_color(str, idx + 2);
	plane = submit_plane(plane, l, n, color);
	push_object(env, plane);
}

t_plane		init_plane(t_p3d o, t_p3d n, double color)
{
	t_plane plane;

	plane.origin = o;
	plane.normal = v_norm(n);
	plane.color = color;
	return (plane);
}

double		intersect_plane(void *p, t_ray *ray)
{
	double	t;
	double	numer;
	double	denom;
	t_plane	*plane;

	plane = (t_plane *)p;
	numer = dot_product(
		vmult(vsub(ray->origin, plane->origin), -1),
		plane->normal);
	denom = dot_product(ray->dir, plane->normal);
	t = numer / denom;
	if (dot_product(ray->dir, plane->normal) > 0)
		plane->normal = vmult(plane->normal, -1);
	if (dot_product(vsub(ray->origin, plane->origin), plane->normal) == 0)
		return (t);
	if (t > 0)
		return (t);
	return (0);
}
