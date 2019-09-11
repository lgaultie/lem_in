/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:24:33 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/11 17:30:40 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dsts;
	unsigned char	*srcs;

	srcs = (unsigned char*)src;
	dsts = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		dsts[i] = srcs[i];
		i++;
	}
	return (dsts);
}
