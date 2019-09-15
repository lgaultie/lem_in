/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:15:46 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/15 11:36:27 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tab;

	size++;
	tab = (char*)malloc(sizeof(char) * size);
	if (tab == NULL)
		return (NULL);
	while (size > 0)
	{
		tab[size - 1] = 0;
		size--;
	}
	return (tab);
}
