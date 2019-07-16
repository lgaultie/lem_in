/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:59:26 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/13 21:15:08 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned char		*s;
	unsigned char		*d;

	i = 0;
	s = (unsigned char *)s1;
	d = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && s[i] == d[i] && s[i] != '\0' && d[i] != '\0')
		i++;
	return (s[i] - d[i]);
}
