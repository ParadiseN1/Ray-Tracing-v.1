/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:20:49 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/25 17:20:50 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char *dst;
	unsigned char *s;

	dst = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dst <= s || dst >= (s + len))
	{
		while (len--)
			*dst++ = *s++;
	}
	else
	{
		dst += len - 1;
		s += len - 1;
		while (len--)
			*dst-- = *s--;
	}
	return (dest);
}
