/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:56:08 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/16 08:22:11 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char			*s1_cpy;
	char			*s2_cpy;
	unsigned int	c;

	s1_cpy = (char*)s1;
	s2_cpy = (char*)s2;
	c = 0;
	while (c < n)
	{
		if (s1_cpy[c] - s2_cpy[c] != 0)
			return ((unsigned char)s1_cpy[c] - (unsigned char)s2_cpy[c]);
		c++;
	}
	return (0);
}
