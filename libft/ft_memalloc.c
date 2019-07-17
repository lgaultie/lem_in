/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:24:17 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 11:12:35 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*bytes;

	bytes = (char*)malloc(sizeof(char) * size);
	if (bytes == NULL)
		return (NULL);
	while (size > 0)
	{
		bytes[size - 1] = 0;
		size--;
	}
	return ((void*)bytes);
}
