/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:13:08 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 15:09:28 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	c_h;
	unsigned int	c_n;
	unsigned int	size_needle;

	c_h = 0;
	c_n = 0;
	size_needle = 0;
	while (needle[size_needle] != '\0')
		size_needle++;
	if (size_needle == 0)
		return ((char*)haystack);
	while (haystack[c_h] != '\0')
	{
		while (needle[c_n] == haystack[c_h + c_n] && c_h + c_n < len)
		{
			if (c_n == size_needle - 1)
				return ((char*)(haystack + c_h));
			c_n++;
		}
		c_n = 0;
		c_h++;
	}
	return (NULL);
}
