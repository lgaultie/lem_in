/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:41:47 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 10:25:17 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int	c;

	c = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (c < n)
	{
		if (s1[c] != s2[c])
			return (0);
		if (s1[c] == '\0' && s2[c] == '\0')
			return (1);
		c++;
	}
	return (1);
}
