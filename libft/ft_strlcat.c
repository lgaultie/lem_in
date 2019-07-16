/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:24 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/14 16:01:10 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			taille_src;
	size_t			taille_dst;
	unsigned char	*srcs;

	taille_src = ft_strlen(src);
	taille_dst = ft_strlen(dst);
	srcs = (unsigned char*)src;
	i = 0;
	if (size < taille_dst)
		return (taille_src + size);
	while (size > taille_dst + i + 1 && srcs[i] != '\0')
	{
		dst[taille_dst + i] = srcs[i];
		i++;
	}
	dst[taille_dst + i] = '\0';
	return (taille_src + taille_dst);
}
