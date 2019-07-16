/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:53:08 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/24 11:50:58 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*newlist;
	t_list	*res;

	if (lst == NULL || f == NULL)
		return (NULL);
	tmp = f(lst);
	if (!(newlist = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	res = newlist;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		newlist->next = ft_lstnew(tmp->content, tmp->content_size);
		newlist = newlist->next;
		lst = lst->next;
	}
	return (res);
}
