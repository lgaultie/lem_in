/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:17:35 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/16 15:06:14 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*tab;

	i = 0;
	if (!(tab = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size + 1)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}
