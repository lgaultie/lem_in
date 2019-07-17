/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:03:24 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 08:12:20 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
		count++;
	}
	return (dst);
}
