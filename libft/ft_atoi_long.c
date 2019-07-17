/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:33:38 by cmouele           #+#    #+#             */
/*   Updated: 2019/06/18 19:50:51 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi_long(const char *str)
{
	long	count;
	long	sign;
	long	nb;

	count = 0;
	sign = 1;
	nb = 0;
	while (str[count] == ' ' || str[count] == '\t' || str[count] == '\n' ||
		str[count] == '\v' || str[count] == '\f' || str[count] == '\r')
		count++;
	if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	else if (str[count] == '+')
		count++;
	while (str[count] >= '0' && str[count] <= '9')
	{
		nb *= 10;
		nb += str[count] - '0';
		count++;
	}
	return (sign * nb);
}
