/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 08:01:30 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 08:01:51 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_prime(int nb)
{
	int counter;

	counter = 3;
	if (nb <= 1 || (nb % 2 == 0 && nb != 2))
		return (0);
	if (nb == 2 || nb == 2147483647)
		return (1);
	while (counter < nb)
	{
		if (nb % counter == 0)
			return (0);
		counter += 2;
	}
	return (1);
}
