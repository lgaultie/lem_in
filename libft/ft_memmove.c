/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:08:33 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/16 09:59:01 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	count;
	char			*dst_cpy;
	const char		*src_cpy;

	count = 0;
	dst_cpy = (char*)dst;
	src_cpy = (const char*)src;
	if ((dst_cpy > src_cpy) && (dst_cpy < (src_cpy + len)))
	{
		while (len > count)
		{
			dst_cpy[len - 1] = src_cpy[len - 1];
			len--;
		}
	}
	else
	{
		while (count < len)
		{
			dst_cpy[count] = src_cpy[count];
			count++;
		}
	}
	return (dst);
}
