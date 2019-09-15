/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:40:03 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 08:15:08 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	*s_cpy;

	count = 0;
	s_cpy = (char*)s;
	while (s_cpy[count] != '\0')
	{
		if (s_cpy[count] == (char)c)
			return (s_cpy + count);
		count++;
	}
	if (s_cpy[count] == '\0' && (char)c == '\0')
		return (s_cpy + count);
	return (NULL);
}
