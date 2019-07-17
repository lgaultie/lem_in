/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:52:33 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/16 15:44:15 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	count;
	char			*str_new;

	count = 0;
	str_new = (char*)malloc(sizeof(char) * len + 1);
	if (s == NULL)
		return (NULL);
	if (str_new == NULL)
		return (NULL);
	while (count < len)
	{
		str_new[count] = s[start + count];
		count++;
	}
	str_new[count] = '\0';
	return (str_new);
}
