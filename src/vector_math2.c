/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:03:21 by vprypesh          #+#    #+#             */
/*   Updated: 2018/06/29 15:03:22 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_p3d		v_norm(t_p3d vec)
{
	t_p3d norm_vector;

	norm_vector.x = vec.x / v_len(vec);
	norm_vector.y = vec.y / v_len(vec);
	norm_vector.z = vec.z / v_len(vec);
	return (norm_vector);
}

double		dot(t_p3d vec)
{
	double len;

	len = v_len(vec);
	return (len * len);
}

double		distance(t_p3d vec1, t_p3d vec2)
{
	t_p3d res;

	res.x = fabs(vec1.x - vec2.x);
	res.y = fabs(vec1.y - vec2.y);
	res.z = fabs(vec1.z - vec2.z);
	return (v_len(res));
}

t_p3d		vadd(t_p3d vec1, t_p3d vec2)
{
	t_p3d	new_vec;

	new_vec.x = vec1.x + vec2.x;
	new_vec.y = vec1.y + vec2.y;
	new_vec.z = vec1.z + vec2.z;
	return (new_vec);
}

t_p3d		vsub(t_p3d vec1, t_p3d vec2)
{
	t_p3d	new_vec;

	new_vec.x = vec1.x - vec2.x;
	new_vec.y = vec1.y - vec2.y;
	new_vec.z = vec1.z - vec2.z;
	return (new_vec);
}
