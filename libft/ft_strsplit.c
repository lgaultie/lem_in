/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:09:23 by cmouele           #+#    #+#             */
/*   Updated: 2019/08/21 14:56:52 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_chars(char const *s, char c)
{
	int	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static int	ft_fill_words(char const *s, char c, char *word)
{
	int	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
	{
		word[count] = s[count];
		count++;
	}
	word[count] = '\0';
	return (count);
}

static void	ft_browse_words(char const *s, char c, char **word_array)
{
	int	size_s;
	int	size_word;

	size_s = 0;
	size_word = 0;
	while (s[size_s] != '\0')
	{
		if (s[size_s] != c)
		{
			word_array[size_word] =
			(char*)malloc(sizeof(char) * (ft_count_chars(s + size_s, c) + 1));
			if (word_array[size_word] != NULL)
				size_s += ft_fill_words(s + size_s, c, word_array[size_word]);
			size_word++;
		}
		else
			size_s++;
	}
	word_array[size_word] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	int		count_char;
	int		count_word;
	char	**word_array;

	if (s == NULL)
		return (NULL);
	count_char = 0;
	count_word = 0;
	while (s[count_char] != '\0')
	{
		if (s[count_char] != c && s[count_char] != '\0')
		{
			count_word++;
			while (s[count_char] != c && s[count_char] != '\0')
				count_char++;
		}
		else
			count_char++;
	}
	word_array = (char**)malloc(sizeof(char*) * (count_word + 1));
	if (word_array == NULL)
		return (NULL);
	else
		ft_browse_words(s, c, word_array);
	return (word_array);
}
