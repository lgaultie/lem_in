/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:10:42 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 08:18:48 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int	count_s1;
	unsigned int	count_s2;

	count_s1 = 0;
	count_s2 = 0;
	while (s1[count_s1] != '\0')
		count_s1++;
	while (s2[count_s2] != '\0' && count_s2 < n)
	{
		s1[count_s1] = s2[count_s2];
		count_s1++;
		count_s2++;
	}
	s1[count_s1] = '\0';
	return (s1);
}
