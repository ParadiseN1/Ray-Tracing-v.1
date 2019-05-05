/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <vprypesh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:09:38 by vprypesh          #+#    #+#             */
/*   Updated: 2018/10/07 14:09:38 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		hex_len(char *str, int i)
{
	int k;
	int j;
	int val;

	k = 0;
	j = 0;
	(str[i] == 'A') ? val = AA : 0;
	(str[i] == 'B') ? val = BB : 0;
	(str[i] == 'C') ? val = CC : 0;
	(str[i] == 'D') ? val = DD : 0;
	(str[i] == 'E') ? val = EE : 0;
	(str[i] == 'F') ? val = FF : 0;
	(str[i] <= '9') ? val = str[i] - '0' : 0;
	while (str[j] != '\0')
	{
		if ((str[j] >= '0' && str[j] <= '9')
		|| (str[j] >= 'A' && str[j] <= 'F'))
			k++;
		else
			return (k - 1);
		j++;
	}
	return (val * pow(16, k - 1 - i));
}

int		hex_atoi(char *str)
{
	int		i;
	int		res;
	int		val;

	val = 0;
	i = 0;
	res = 0;
	while (isspace(str[i]))
		i++;
	if (str[i] == '#')
		i++;
	else
		return (0);
	str = &str[i];
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9')
		|| (str[i] >= 'A' && str[i] <= 'F'))
			res += hex_len(str, i);
		else
			return (res);
		i++;
	}
	return (res);
}

double	calc_res(int first, double second, int sign)
{
	double	res;
	int		k;

	k = 1;
	res = 0;
	while (k)
	{
		if ((double)(second / k) < 1)
		{
			if (first >= 0)
				res = (double)first + (double)second * sign / k;
			else
				res = (double)first - (double)second / k;
			break ;
		}
		k *= 10;
	}
	return (res);
}

double	sec_part(char *str, int i)
{
	double	del;

	del = 1;
	while (str[++i] != '\0' && str[i] != ',')
	{
		if (str[i] == '.')
		{
			while (str[i + 1] == '0' && ft_atoi(&str[i + 1]) != 0)
			{
				i++;
				(del == 1) ? (del *= 100) : (del *= 10);
			}
			return ((double)ft_atoi(&str[i + 1]) / del);
		}
	}
	return (0);
}

double	float_atoi(char *str)
{
	int		i;
	double	second;
	int		first;
	int		sign;

	sign = 1;
	first = 0;
	second = 0;
	i = 0;
	while (isspace(str[i]))
		i++;
	str = &str[i];
	i = -1;
	if (str[0] == '-' && str[1] == '0')
		sign = -1;
	second = sec_part(str, i);
	first = ft_atoi(str);
	if (second < 0)
		return (0);
	return (calc_res(first, second, sign));
}
