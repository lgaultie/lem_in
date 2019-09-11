/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprintstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:25:20 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/23 14:25:23 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprintstr(t_list *list)
{
	while (list != NULL)
	{
		ft_putstr(list->content);
		ft_putchar('\n');
		list = list->next;
	}
}
