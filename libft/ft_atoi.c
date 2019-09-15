/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:48:35 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/20 08:03:34 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	count;
	int	sign;
	int nb;

	count = 0;
	sign = 1;
	nb = 0;
	while (str[count] == ' ' || str[count] == '\t' || str[count] == '\n'
		|| str[count] == '\v' || str[count] == '\f' || str[count] == '\r')
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
