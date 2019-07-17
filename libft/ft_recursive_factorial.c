/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 08:02:42 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 08:03:10 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_recursive_factorial(int nb)
{
	int result;

	result = 1;
	if (nb > 1 && nb < 13)
		result = nb * ft_recursive_factorial(nb - 1);
	else if (nb == 1 || nb == 0)
		return (1);
	else
		return (0);
	return (result);
}
