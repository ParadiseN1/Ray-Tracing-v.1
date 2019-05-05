/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:43:36 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/27 21:43:37 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		start_pos(const char *s)
{
	int i;
	int start;

	start = 0;
	i = 0;
	if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		{
			i++;
			start++;
		}
	return (start);
}

static int		end_pos(const char *s)
{
	int i;
	int end;

	end = ft_strlen(s);
	i = ft_strlen(s) - 1;
	if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		{
			i--;
			end--;
		}
	return (end);
}

static void		ft_write_sring(int start, int len, char *str, char const *s)
{
	int i;

	i = 0;
	while (start < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		start;
	int		end;

	str = NULL;
	if (!s)
		return (NULL);
	start = start_pos(s);
	end = end_pos(s);
	str = malloc(sizeof(char) * (end - start + 1));
	if (start == (int)ft_strlen(s))
	{
		str = malloc(sizeof(char));
		ft_strcpy(str, "\0");
	}
	else if (str == NULL)
		return (str);
	else
		ft_write_sring(start, end, str, s);
	return (str);
}
