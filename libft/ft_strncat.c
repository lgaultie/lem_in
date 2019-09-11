/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:56:34 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/12 17:23:05 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*srcs;

	i = 0;
	j = 0;
	srcs = (unsigned char*)src;
	while (dst[i] != '\0')
		i++;
	while (srcs[j] != '\0' && j < n)
	{
		dst[i + j] = srcs[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}
