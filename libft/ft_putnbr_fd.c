/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 16:58:41 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/29 16:58:42 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	int		p;
	int		str[10];
	int		i;

	i = 0;
	p = 1;
	if (n < 0)
	{
		p = -1;
		ft_putchar_fd('-', fd);
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	while (n)
	{
		str[i] = (n % 10) * p;
		n = n / 10;
		i++;
	}
	while (i)
	{
		i--;
		ft_putchar_fd(str[i] + '0', fd);
	}
}
