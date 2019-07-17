/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:11:37 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 11:28:49 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start;
	t_list	*current;

	if (lst == NULL || *f == NULL || f == NULL)
		return (NULL);
	start = f(lst);
	if (start == NULL)
		return (NULL);
	current = start;
	lst = lst->next;
	while (lst)
	{
		current->next = f(lst);
		if (current->next == NULL)
			return (NULL);
		current = current->next;
		lst = lst->next;
	}
	return (start);
}
