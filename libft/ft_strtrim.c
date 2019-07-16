/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 20:27:46 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/19 15:05:21 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i] != 0)
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	while ((s[j] == ' ' || s[j] == '\t' || s[j] == '\n') && j >= 0)
		j--;
	str = ft_strsub(s, i, j + 1 - i);
	return (str);
}
