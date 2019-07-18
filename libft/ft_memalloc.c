/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:24:17 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/18 14:08:12 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*bytes;

	bytes = malloc(sizeof(char) * size);
	if (bytes == NULL)
		return (NULL);
	while (size > 0)
	{
		bytes[size - 1] = 0;
		size--;
	}
	return ((void*)bytes);
}
