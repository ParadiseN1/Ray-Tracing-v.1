/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 14:36:58 by vprypesh          #+#    #+#             */
/*   Updated: 2018/04/01 14:36:58 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	push_object(t_env *env, t_object *new)
{
	t_object *tail;

	if (env)
		tail = env->objects;
	else
		tail = NULL;
	if (env->objects == NULL)
		tail = NULL;
	while (tail && tail->next)
		tail = tail->next;
	if (tail == NULL)
	{
		tail = new;
		env->objects = tail;
	}
	else
		tail->next = new;
}

t_vec	get_rgb(int color)
{
	t_vec		rgb;
	Uint8		r;
	Uint8		g;
	Uint8		b;

	r = color >> 16;
	g = (color - (r << 16)) >> 8;
	b = color - (r << 16) - (g << 8);
	rgb = (t_vec){r, g, b};
	return (rgb);
}

Uint32	map_rgb(t_vec rgb)
{
	if ((int)rgb[0] > 255)
		rgb[0] = 255;
	if ((int)rgb[1] > 255)
		rgb[1] = 255;
	if ((int)rgb[2] > 255)
		rgb[2] = 255;
	return (((int)rgb[0] << 16) + ((int)rgb[1] << 8) + (int)rgb[2]);
}

int		clear_img(t_env *env)
{
	Uint32		*pixels;
	int			i;

	i = -1;
	if (env == NULL)
		return (-1);
	pixels = (Uint32 *)env->img->pixels;
	while (++i < WIN_HEIGHT * WIN_WIDTH)
		pixels[i] = 0;
	return (1);
}

int		img_put_pixel(t_env *env, int x, int y, int color)
{
	Uint32	*pixels;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT || env->img == NULL)
		return (-1);
	SDL_LockSurface(env->img);
	pixels = (Uint32 *)env->img->pixels;
	pixels[y * WIN_WIDTH + x] = color;
	SDL_UnlockSurface(env->img);
	return (1);
}
