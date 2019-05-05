/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:53:57 by vprypesh          #+#    #+#             */
/*   Updated: 2018/10/07 12:53:58 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_p3d		write_coords(char *str, Uint32 i, t_p3d obj, t_p3d *ck)
{
	if (str[i] >= '0' && str[i] <= '9'
	&& (str[i - 1] == '(' || str[i - 1] == '-'))
	{
		ck->y = i;
		if (str[i - 1] == '-')
			ck->y--;
	}
	if ((str[i] == ',' && str[i + 1] == ' ') || (str[i] == ')' && ck->x == 2))
	{
		if (ck->x == 0)
			obj.x = float_atoi(str + (Uint32)ck->y);
		else if (ck->x == 1)
			obj.y = float_atoi(str + (Uint32)ck->y);
		else if (ck->x == 2)
			obj.z = float_atoi(str + (Uint32)ck->y);
		ck->x++;
		ck->y = i + 2;
	}
	if (ck->x == 3 && str[i] == ')' && str[i - 1] >= '0' && str[i - 1] <= '9')
		obj.len = float_atoi(&str[(Uint32)ck->y]);
	return (obj);
}

t_p3d		get_coords(char *str)
{
	t_p3d		obj;
	Uint32		i;
	t_p3d		ck;

	ck.x = 0;
	ck.y = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		obj = write_coords(str, i, obj, &ck);
	}
	return (obj);
}

Uint32		get_color(char **str, Uint32 idx)
{
	Uint32 i;
	Uint32 res;

	res = 0;
	i = 0;
	while (str[idx][i])
	{
		if (str[idx][0] != '!')
			return (res);
		if (str[idx][i] == ':' && ft_strncmp(str[idx], "!color:", 7) == 0
			&& ft_strchr(&str[idx][i], '#'))
			res = hex_atoi(&str[idx][i + 1]);
		else if (str[idx][i] == ':' && ft_strncmp(str[idx], "!color:", 7) == 0)
			res = float_atoi(&str[idx][i + 1]);
		i++;
	}
	return (res);
}

void		calc_light(t_env *env, char **str, Uint32 idx)
{
	t_object	*new_light;
	t_p3d		l;
	Uint32		i;

	i = 0;
	new_light = malloc(sizeof(t_object));
	while (str[idx][i] != '\0')
	{
		if (str[idx][0] != '!')
		{
			free(new_light);
			return ;
		}
		if (str[idx][i] == ':' && ft_strncmp(str[idx], "!coords:", i + 1) == 0)
			l = get_coords(&str[idx][i]);
		i++;
	}
	new_light->type = LIGHT;
	new_light->light = init_light(l.x, l.y, l.z, l.len);
	new_light->origin = l;
	new_light->color = 0;
	new_light->next = NULL;
	push_object(env, new_light);
}

Uint32		get_objects(t_env *env)
{
	Uint32	i;
	Uint32	j;
	char	*t;

	if ((t = read_scene(env->path)) == 0)
		return (0);
	env->map = ft_strsplit(t, '\n');
	free(t);
	i = -1;
	while (env->map[++i] != NULL)
	{
		j = -1;
		while (env->map[i][++j] != '\0')
		{
			object_calculations(env, i, j);
		}
	}
	return (1);
}
