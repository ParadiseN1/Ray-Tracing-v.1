/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:53:19 by vprypesh          #+#    #+#             */
/*   Updated: 2018/10/07 12:53:19 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	intersect_object(t_object *cur, t_env *env, t_ray *ray, double light)
{
	double intersect;

	intersect = cur->intersect(cur->obj, ray);
	if (cur != env->active && ((env->dist == 0 && intersect > 0)
	|| (intersect < env->dist && intersect > 0)))
	{
		env->dist = intersect;
		if (light == -1)
		{
			env->active = cur;
			env->old_dist = env->dist;
		}
	}
}

int		trace(t_env *env, t_ray *ray, double light)
{
	t_object	*cur;
	double		intersect;

	env->dist = 0;
	cur = env->objects;
	intersect = 0;
	while (cur)
	{
		next_physical(&cur);
		if (cur == NULL)
			break ;
		intersect_object(cur, env, ray, light);
		cur = cur->next;
	}
	if (!env->active)
		return (0);
	if (light == -1)
		return (calc_color(env->active, env->objects, env, env->old_dist));
	else if (env->dist < light && env->dist > 0)
		return (0);
	return (1);
}

double	back_trace(t_env *env)
{
	t_ray		ray;
	double		res;
	t_object	*cur;
	int			i;

	i = 0;
	cur = env->objects;
	res = 0;
	while (cur)
	{
		if (cur->type == LIGHT)
		{
			ray.origin = vadd(env->ray.origin,
			vmult(env->ray.dir, env->old_dist));
			ray.dir = v_norm(vsub(cur->light.position, ray.origin));
			if (dot_product(ray.dir, env->active->normal) > 0.05)
				res += trace(env, &ray, distance(ray.origin,
				cur->light.position));
			else
				res++;
			i++;
		}
		cur = cur->next;
	}
	return (res / i);
}

void	trace_ray(t_env *env, double x, double y)
{
	double d;
	double color;

	d = WIN_WIDTH * cos(PI / 6);
	env->ray.dir = vadd(vmult(env->cam.u, x), vmult(env->cam.v, y));
	env->ray.dir = vadd(vmult(env->cam.w, d), env->ray.dir);
	env->ray.dir = v_norm(env->ray.dir);
	env->ray.origin = env->default_ray.origin;
	env->active = NULL;
	env->color = (t_vec){0, 0, 0};
	color = 0;
	if (trace(env, &env->ray, -1))
		color = back_trace(env);
	env->color *= (t_vec){color, color, color};
	color = map_rgb(env->color);
	if (color > 0)
		img_put_pixel(env, x + WIN_WIDTH / 2, y + WIN_HEIGHT / 2, color);
	else
		img_put_pixel(env, x + WIN_WIDTH / 2, y + WIN_HEIGHT / 2, 0);
}

int		tracer(t_env *env)
{
	double y;
	double x;

	y = (WIN_HEIGHT / 2) - WIN_HEIGHT;
	x = (WIN_WIDTH / 2) - WIN_WIDTH;
	env->default_ray = env->ray;
	while (y < WIN_HEIGHT / 2)
	{
		while (x < WIN_WIDTH / 2)
		{
			trace_ray(env, x, y);
			x++;
		}
		x = WIN_WIDTH / 2 - WIN_WIDTH;
		y++;
	}
	SDL_UpdateWindowSurface(env->win);
	return (1);
}
