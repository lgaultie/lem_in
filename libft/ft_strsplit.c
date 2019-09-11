/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 10:55:33 by lgaultie          #+#    #+#             */
/*   Updated: 2019/06/21 11:21:42 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		countwords(char const *s, char c)
{
	size_t	compteur;
	size_t	i;

	i = 0;
	compteur = 0;
	while (i < ft_strlen(s))
	{
		if (i == 0 && s[i] != c)
			compteur++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			compteur++;
		i++;
	}
	return (compteur);
}

static int		countchar(char const *str, int i, char c)
{
	int nbrchar;

	nbrchar = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c)
			nbrchar++;
		else
			return (nbrchar);
		i++;
	}
	return (nbrchar);
}

char			**ft_strsplit2(char const *s, char c, int i, int j)
{
	char	**ret;
	int		k;
	int		nbrchar;

	nbrchar = countwords(s, c);
	if (!s)
		return (0);
	if (!(ret = (char **)malloc(sizeof(char *) * (nbrchar + 1))))
		return (0);
	while (j < nbrchar)
	{
		k = 0;
		while (s[i] == ' ')
			i++;
		if (!(ret[j] = ft_strnew(countchar(s, i, c))))
			return (0);
		while (s[i] && s[i] != c)
			ret[j][k++] = s[i++];
		i++;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	return (ft_strsplit2(s, c, i, j));
}
