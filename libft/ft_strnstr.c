/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:42:10 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/24 19:42:11 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int		l1;
	int		l2;
	char	*haystack;
	char	*needle;

	haystack = (char *)str;
	needle = (char *)to_find;
	l1 = 0;
	if (needle[0] == 0)
		return (haystack);
	while (haystack[l1] != '\0' && l1 < (int)len)
	{
		l2 = 0;
		while (haystack[l1] == needle[l2] && l1 < (int)len)
		{
			if (needle[l2 + 1] == '\0')
				return (&(*(haystack + l1 - l2)));
			l1++;
			l2++;
		}
		l1 = l1 - l2;
		l1++;
	}
	return (0);
}
