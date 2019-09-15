/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:07:27 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/19 09:49:35 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fill_cpy(int start, int end, char const *s, char *s_cpy)
{
	int count_scpy;

	count_scpy = 0;
	while (count_scpy < end - start)
	{
		s_cpy[count_scpy] = s[start + count_scpy];
		count_scpy++;
	}
	return (count_scpy);
}

char		*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	char	*s_cpy;
	int		count_scpy;

	if (s == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	count_scpy = 0;
	while (s[start] && (s[start] == ' ' || s[start] == '\n'
						|| s[start] == '\t'))
		start++;
	while ((end - 1) >= 0 && (s[end - 1] == ' ' || s[end - 1] == '\n'
						|| s[end - 1] == '\t'))
		end--;
	if (end - start <= 0)
		s_cpy = (char*)malloc(sizeof(char) * 1);
	else
		s_cpy = (char*)malloc(sizeof(char) * (end - start + 1));
	if (s_cpy == NULL)
		return (NULL);
	count_scpy = ft_fill_cpy(start, end, s, s_cpy);
	s_cpy[count_scpy] = '\0';
	return (s_cpy);
}
