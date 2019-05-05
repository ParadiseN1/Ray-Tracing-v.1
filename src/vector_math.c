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

t_p3d		vmult(t_p3d vec, double a)
{
	t_p3d	new_vec;

	new_vec.x = vec.x * a;
	new_vec.y = vec.y * a;
	new_vec.z = vec.z * a;
	return (new_vec);
}

t_p3d		vdiv(t_p3d vec, double a)
{
	t_p3d	new_vec;

	new_vec.x = vec.x / a;
	new_vec.y = vec.y / a;
	new_vec.z = vec.z / a;
	return (new_vec);
}

double		dot_product(t_p3d v1, t_p3d v2)
{
	double res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

double		v_len(t_p3d vec)
{
	return ((double)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
