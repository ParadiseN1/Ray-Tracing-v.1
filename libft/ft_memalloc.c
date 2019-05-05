/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:26:57 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/27 18:26:58 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*memory;
	int		i;

	i = 0;
	memory = (void *)malloc(size);
	if (memory == NULL)
		return (NULL);
	while (i < (int)size)
	{
		memory[i] = 0;
		i++;
	}
	return ((void *)memory);
}
