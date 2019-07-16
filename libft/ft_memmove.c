/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:58:29 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/14 16:31:28 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dsts;
	unsigned char	*srcs;

	i = 0;
	srcs = (unsigned char*)src;
	dsts = (unsigned char*)dst;
	if (srcs < dsts)
	{
		len--;
		while (len + 1 > 0)
		{
			dsts[len] = srcs[len];
			len--;
		}
	}
	if (srcs > dsts)
	{
		while (i < len)
		{
			dsts[i] = srcs[i];
			i++;
		}
	}
	return (dsts);
}
