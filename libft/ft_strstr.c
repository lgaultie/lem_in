/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:04:08 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/12 15:26:17 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *needle)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i] != needle[j] && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (0);
		while (str[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char*)str + i);
			j++;
		}
		i++;
	}
	return (0);
}
