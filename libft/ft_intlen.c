/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:16:46 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/23 15:25:21 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(int nb)
{
	int		count;

	count = 0;
	if (nb > 2147483647 || nb < -2147483648)
		return (0);
	if (nb >= 0 && nb < 10)
		return (++count);
	if (nb > -10 && nb < 0)
	{
		nb = nb * -1;
		return (2);
	}
	if (nb < 0)
	{
		nb = nb * (-1);
		count++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}
