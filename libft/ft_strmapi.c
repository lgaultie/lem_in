/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:27:01 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/16 15:48:55 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		count;
	int		count_new;
	char	*s_new;

	count = 0;
	count_new = 0;
	if (s == NULL)
		return (NULL);
	while (s[count] != '\0')
		count++;
	s_new = (char*)malloc(sizeof(char) * count + 1);
	if (s_new == NULL)
		return (NULL);
	while (count_new < count)
	{
		s_new[count_new] = f(count_new, s[count_new]);
		count_new++;
	}
	s_new[count_new] = '\0';
	return (s_new);
}
