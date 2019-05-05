/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:27:31 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/25 18:27:31 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
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
		if ((char)src1[i] == c)
		{
			dst = dest;
			return (&dst[i + 1]);
		}
		i++;
	}
	return (NULL);
}
