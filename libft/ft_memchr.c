/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:39:43 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/13 20:25:27 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	d;
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char*)s;
	d = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == d)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
