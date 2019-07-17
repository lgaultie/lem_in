/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:34:23 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 10:43:08 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	count;

	count = 0;
	if (s1 && s2)
	{
		while (s1[count] == s2[count])
		{
			if (s1[count] == '\0' && s2[count] == '\0')
				return (1);
			count++;
		}
	}
	return (0);
}
