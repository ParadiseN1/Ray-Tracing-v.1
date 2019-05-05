/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:16:54 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/25 20:16:54 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*src1;
	int		i;

	i = 0;
	dest = (char *)dst;
	src1 = (char *)src;
	while (i < (int)n)
	{
		dest[i] = src1[i];
		i++;
	}
	dst = dest;
	return (dst);
}
