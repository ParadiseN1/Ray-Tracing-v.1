/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:04:45 by vprypesh          #+#    #+#             */
/*   Updated: 2019/04/12 18:04:46 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		clear_actions(t_act *actions)
{
	actions->height = 0;
	actions->sides = 0;
	actions->dist = 0;
	actions->any = 0;
	actions->cam_u = 0;
	actions->cam_w = 0;
	actions->cam_v = 0;
}

t_env		init(t_env *env)
{
	env->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	env->img = SDL_GetWindowSurface(env->win);
	env->cam.origin.x = 0;
	env->cam.origin.y = 0;
	env->cam.origin.z = -2;
	env->cam.w.x = 0;
	env->cam.w.y = 0;
	env->cam.w.z = 1;
	env->cam.u.x = 1;
	env->cam.u.y = 0;
	env->cam.u.z = 0;
	env->cam.v.x = 0;
	env->cam.v.y = -1;
	env->cam.v.z = 0;
	env->objects = NULL;
	return (*env);
}

void		looper(t_env *env)
{
	int			screen;
	SDL_Event	e;
	t_object	*obj;
	t_object	*next;

	screen = 1;
	next = NULL;
	while (screen)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN
			&& e.key.keysym.sym == SDLK_ESCAPE))
				screen = 0;
		}
	}
	obj = env->objects;
	(obj != NULL) ? next = obj->next : 0;
	while (next)
	{
		next = obj->next;
		free(obj);
		obj = NULL;
		obj = next;
	}
}

t_object	*fix_objects(t_env *env)
{
	t_object *cur;

	cur = env->objects;
	while (cur)
	{
		if (cur->type == SPHERE)
		{
			cur->obj = &cur->sphere;
		}
		else if (cur->type == PLANE)
		{
			cur->obj = &cur->plane;
		}
		else if (cur->type == CYLINDER)
		{
			cur->obj = &cur->cylinder;
		}
		else if (cur->type == CONE)
		{
			cur->obj = &cur->cone;
		}
		cur = cur->next;
	}
	return (env->objects);
}

int			main(int argc, char **argv)
{
	t_env env;

	if (argc == 2 && valid_format(argv[1]) == 1)
		env.path = argv[1];
	else
	{
		write(1, "Arguments not correct\nExiting...\n", 33);
		return (1);
	}
	env = init(&env);
	if (get_objects(&env) == 0)
	{
		write(1, "Error\nExiting...\n", 17);
		return (1);
	}
	env.ray.origin = env.cam.origin;
	env.objects = (void *)fix_objects(&env);
	tracer(&env);
	looper(&env);
	return (0);
}
