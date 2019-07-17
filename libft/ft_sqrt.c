/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 08:05:38 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 08:06:00 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	int counter;

	counter = 0;
	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	while (counter <= nb && counter <= 46340)
	{
		if (counter * counter == nb)
			return (counter);
		counter++;
	}
	return (0);
}
