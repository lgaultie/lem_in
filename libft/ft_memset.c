/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:24:47 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/14 11:15:40 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	char			*tab;

	i = 0;
	tab = (char*)b;
	while (i < len)
	{
		tab[i] = c;
		i++;
	}
	return ((void*)tab);
}
