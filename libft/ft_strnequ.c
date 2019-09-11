/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:19:58 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/15 19:04:36 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (n == 0)
		return (1);
	while (i < n - 1 && s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	if ((unsigned char)s1[i] - (unsigned char)s2[i] == 0)
		return (1);
	return (0);
}
