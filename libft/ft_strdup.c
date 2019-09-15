/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:06:43 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 08:20:23 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlength(const char *s)
{
	unsigned int count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char			*ft_strdup(const char *s1)
{
	char	*dst;
	int		count;

	count = 0;
	dst = (char*)malloc(sizeof(char) * (ft_strlength(s1) + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[count] != '\0')
	{
		dst[count] = s1[count];
		count++;
	}
	dst[count] = '\0';
	return (dst);
}
