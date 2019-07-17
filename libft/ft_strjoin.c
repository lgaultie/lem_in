/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:05:51 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/19 09:19:27 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_join_chars(char *new_str, char const *s1, char const *s2,
						unsigned int size_str)
{
	unsigned int	count;
	unsigned int	count_s1;
	unsigned int	count_s2;

	count = 0;
	count_s1 = 0;
	count_s2 = 0;
	while (count < size_str)
	{
		while (s1[count_s1] != '\0')
		{
			new_str[count] = s1[count_s1];
			count_s1++;
			count++;
		}
		while (s2[count_s2] != '\0')
		{
			new_str[count] = s2[count_s2];
			count_s2++;
			count++;
		}
	}
	return (count);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_str;
	unsigned int	size_str;
	unsigned int	count;
	unsigned int	count_s1;
	unsigned int	count_s2;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	count_s1 = 0;
	count_s2 = 0;
	size_str = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char*)malloc(sizeof(char) * (size_str + 1));
	if (new_str == NULL)
		return (NULL);
	count = ft_join_chars(new_str, s1, s2, size_str);
	new_str[count] = '\0';
	return (new_str);
}
