/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:30:53 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/23 14:31:26 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_display_array(char **tab)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = 0;
	while (tab[i] != NULL)
	{
		size++;
		i++;
	}
	i = 0;
	while (i < size)
	{
		while (tab[i][j] != '\0')
		{
			ft_putchar(tab[i][j]);
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
}
