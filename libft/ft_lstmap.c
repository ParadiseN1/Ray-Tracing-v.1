/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 20:48:57 by vprypesh          #+#    #+#             */
/*   Updated: 2017/10/29 20:48:57 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *prev;
	t_list *new_list;

	if (lst && f)
	{
		prev = f(ft_lstnew(lst->content, lst->content_size));
		new_list = prev;
		lst = lst->next;
		while (lst)
		{
			prev->next = f(ft_lstnew(lst->content, lst->content_size));
			prev = prev->next;
			lst = lst->next;
		}
		return (new_list);
	}
	return (NULL);
}
