/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:08:23 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 15:27:43 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	count_dst;
	unsigned int	count_src;
	unsigned int	length_dst;
	unsigned int	length_src;

	count_dst = 0;
	count_src = 0;
	length_src = 0;
	while (dst[count_dst] != '\0')
		count_dst++;
	length_dst = count_dst;
	while (src[length_src] != '\0')
		length_src++;
	if (dstsize < length_dst)
		return (dstsize + length_src);
	while (src[count_src] != '\0' && count_dst < dstsize - 1)
	{
		dst[count_dst] = src[count_src];
		count_dst++;
		count_src++;
	}
	dst[count_dst] = '\0';
	return (length_dst + length_src);
}
