/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:29:53 by vprypesh          #+#    #+#             */
/*   Updated: 2018/10/07 19:29:54 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_light	init_light(double x, double y, double z, double intensity)
{
	t_light light;

	light.position.x = x;
	light.position.y = y;
	light.position.z = z;
	light.intensity = intensity;
	light.color = get_rgb(0xFFFFFF);
	return (light);
}

double	my_phong(t_p3d l, t_p3d v, t_p3d n)
{
	t_p3d	h;
	double	k;

	h = v_norm(vadd(l, v));
	k = dot_product(h, n);
	k = pow(k, 1000);
	return (k);
}

t_koef	add_compute_lightning(t_p3d point, t_p3d n, t_object *obj, t_p3d v)
{
	double		i;
	t_p3d		l;
	t_object	*cur;
	t_koef		res;

	cur = obj;
	i = 0;
	res.phong = 0;
	res.lamb = 0;
	while (cur)
	{
		if (cur->type == LIGHT)
		{
			l = v_norm(vsub(cur->light.position, point));
			if (dot_product(n, l) >= 0)
			{
				res.lamb += cur->light.intensity * dot_product(n, l);
				res.phong += my_phong(l, v, n) * cur->light.intensity;
			}
		}
		cur = cur->next;
	}
	(res.lamb > 1) ? res.lamb = 1 : 0;
	(res.phong > 1) ? res.phong = 1 : 0;
	return (res);
}

void	set_norm(t_object **this_obj)
{
	if ((*this_obj)->type == SPHERE)
		(*this_obj)->normal = (*this_obj)->sphere.normal;
	else if ((*this_obj)->type == PLANE)
		(*this_obj)->normal = (*this_obj)->plane.normal;
	else if ((*this_obj)->type == CYLINDER)
		(*this_obj)->normal = (*this_obj)->cylinder.normal;
	else if ((*this_obj)->type == CONE)
		(*this_obj)->normal = (*this_obj)->cone.normal;
}

double	calc_color(t_object *this_obj, t_object *obj, t_env *env, double dist)
{
	t_p3d	point;
	Sint32	color;
	t_vec	rgb;
	t_p3d	v;
	t_koef	bright;

	color = 0;
	point = vadd(env->ray.origin, vmult(env->ray.dir, dist));
	v = v_norm(vsub(env->cam.origin, point));
	if (this_obj->type != LIGHT)
	{
		set_norm(&this_obj);
		rgb = get_rgb(this_obj->color);
		bright = add_compute_lightning(point, this_obj->normal, obj, v);
		rgb = (rgb * (t_vec){bright.lamb, bright.lamb, bright.lamb});
		bright.phong *= 255;
		rgb = (rgb + (t_vec){bright.phong, bright.phong, bright.phong});
		color = map_rgb(rgb);
		env->color = rgb;
	}
	return (color);
}
