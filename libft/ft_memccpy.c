/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 10:11:58 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/16 10:24:18 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	count;
	char			*dst_cpy;
	char			*src_cpy;

	count = 0;
	dst_cpy = (char*)dst;
	src_cpy = (char*)src;
	while (count < n)
	{
		dst_cpy[count] = src_cpy[count];
		if ((unsigned char)src_cpy[count] == (unsigned char)c)
			return ((void*)(dst_cpy + count + 1));
		count++;
	}
	return (NULL);
}
