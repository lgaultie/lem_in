/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:14:08 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 15:09:45 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	count_haystack;
	int	count_needle;
	int size_needle;

	count_haystack = 0;
	count_needle = 0;
	size_needle = 0;
	while (needle[size_needle] != '\0')
		size_needle++;
	if (size_needle == 0)
		return ((char*)haystack);
	while (haystack[count_haystack] != '\0')
	{
		while (needle[count_needle] == haystack[count_haystack + count_needle])
		{
			if (count_needle == size_needle - 1)
				return ((char*)(haystack + count_haystack));
			count_needle++;
		}
		count_needle = 0;
		count_haystack++;
	}
	return (NULL);
}
