/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 21:18:34 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/29 15:30:16 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_write_str(char *str, int length, int n)
{
	char *tmp;

	tmp = malloc(sizeof(char) * length + 1);
	tmp[length] = '\0';
	length--;
	if (n < 0)
		tmp[0] = '-';
	while (n)
	{
		if (tmp[0] == '-')
			tmp[length] = (n % 10) * (-1) + '0';
		else
			tmp[length] = (n % 10) + '0';
		n = n / 10;
		length--;
	}
	ft_strcpy(str, tmp);
	free(tmp);
}

char		*ft_itoa(int n)
{
	int		length;
	char	*str;
	int		k;

	k = n;
	length = 0;
	while (k)
	{
		k = k / 10;
		length++;
	}
	if (n < 0)
		length++;
	if (n == 0)
	{
		str = malloc(sizeof(char) * 2);
		ft_strcpy(str, "0\0");
		return (str);
	}
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (str);
	ft_write_str(str, length, n);
	return (str);
}
