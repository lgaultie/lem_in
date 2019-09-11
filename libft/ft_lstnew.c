/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:26:36 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/23 14:44:59 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_maillon;

	if (!(new_maillon = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (content_size > 0)
		{
			if (!(new_maillon->content = (void*)malloc(content_size)))
				return (NULL);
			ft_memcpy(new_maillon->content, content, content_size);
		}
		else
			new_maillon->content = (void*)content;
		new_maillon->content_size = content_size;
	}
	else
	{
		new_maillon->content = NULL;
		new_maillon->content_size = 0;
	}
	new_maillon->next = NULL;
	return (new_maillon);
}
