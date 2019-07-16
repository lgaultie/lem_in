/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:34:34 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/17 15:12:52 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int				i;
	int				j;
	unsigned char	*srcs;

	i = 0;
	j = 0;
	srcs = (unsigned char*)src;
	while (dst[i] != '\0')
		i++;
	while (srcs[j] != '\0')
	{
		dst[i + j] = srcs[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}
