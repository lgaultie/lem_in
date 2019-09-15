/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 09:35:31 by cmouele           #+#    #+#             */
/*   Updated: 2019/01/21 09:35:36 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *last_elem;

	if (alst && new)
	{
		new->next = NULL;
		if (*alst == NULL)
			*alst = new;
		else
		{
			last_elem = *alst;
			while (last_elem->next)
			{
				last_elem = last_elem->next;
			}
			last_elem->next = new;
		}
	}
}
