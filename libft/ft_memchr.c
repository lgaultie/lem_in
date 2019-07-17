/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:34:42 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 08:07:40 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*s_cpy;
	unsigned int	count;

	s_cpy = (char*)s;
	count = 0;
	while (count < n)
	{
		if (s_cpy[count] == (char)c)
			return ((void*)(s_cpy + count));
		count++;
	}
	return (NULL);
}
