/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 10:53:43 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/16 15:48:22 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		s_new[count_new] = f(s[count_new]);
		count_new++;
	}
	s_new[count_new] = '\0';
	return (s_new);
}
