/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:45:04 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/15 16:08:22 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	d;

	i = 0;
	str = (char*)s;
	d = (char)c;
	while (str[i] != '\0')
		i++;
	while (i >= 0 && str[i] != d)
		i--;
	if (str[i] == d)
		return ((char*)&str[i]);
	return (NULL);
}
