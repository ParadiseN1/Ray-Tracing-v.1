/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:53:37 by vprypesh          #+#    #+#             */
/*   Updated: 2019/04/13 11:53:38 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			valid_format(char *file_name)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char) * ft_strlen(file_name));
	i = (int)ft_strlen(file_name) - 1;
	while (i >= 0 && file_name[i + 1] != '.')
	{
		str[j] = file_name[i];
		i--;
		j++;
	}
	str[j] = '\0';
	str = ft_strrev(str);
	if (ft_strcmp(str, ".txt") == 0)
	{
		ft_strdel(&str);
		return (1);
	}
	ft_strdel(&str);
	return (-1);
}

void		calc_cam(t_env *env, char **str, Uint32 idx)
{
	Uint32		i;

	i = -1;
	while (str[idx][++i] != '\0')
	{
		if (str[idx][0] != '!')
			return ;
		if (str[idx][i] == ':' && ft_strncmp(str[idx], "!origin:", i + 1) == 0)
			env->cam.origin = get_coords(&str[idx][i]);
		if (str[idx + 1][i] == ':'
						&& ft_strncmp(str[idx + 1], "!up:", i + 1) == 0)
			env->cam.v = get_coords(&str[idx + 1][i]);
		if (str[idx + 2][i] == ':'
						&& ft_strncmp(str[idx + 2], "!right:", i + 1) == 0)
			env->cam.u = get_coords(&str[idx + 2][i]);
		if (str[idx + 3][i] == ':'
						&& ft_strncmp(str[idx + 3], "!back:", i + 1) == 0)
			env->cam.w = get_coords(&str[idx + 3][i]);
	}
}

void		object_calculations(t_env *env, Uint32 i, Uint32 j)
{
	if (env->map[i][j] == '#'
				&& ft_strncmp(env->map[i] + j, "#SPHERE", 7) == 0)
		calc_sphere(env, env->map, i + 1);
	else if (env->map[i][j] == '#'
				&& ft_strncmp(env->map[i] + j, "#LIGHT", 6) == 0)
		calc_light(env, env->map, i + 1);
	else if (env->map[i][j] == '#'
				&& ft_strncmp(env->map[i] + j, "#PLANE", 6) == 0)
		calc_plane(env, env->map, i + 1);
	else if (env->map[i][j] == '#'
				&& ft_strncmp(env->map[i] + j, "#CYLINDER", 9) == 0)
		calc_cylinder(env, env->map, i + 1);
	else if (env->map[i][j] == '#'
				&& ft_strncmp(env->map[i] + j, "#CONE", 5) == 0)
		calc_cone(env, env->map, i + 1);
	else if (env->map[i][j] == '#'
				&& ft_strncmp(env->map[i] + j, "#CAMERA", 7) == 0)
		calc_cam(env, env->map, i + 1);
}
