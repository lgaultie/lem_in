/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:22:17 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/19 08:31:12 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putnbr_max(void)
{
	ft_putchar('-');
	ft_putchar('2');
	ft_putchar('1');
	ft_putchar('4');
	ft_putchar('7');
	ft_putchar('4');
	ft_putchar('8');
	ft_putchar('3');
	ft_putchar('6');
	ft_putchar('4');
	ft_putchar('8');
}

void			ft_putnbr(int n)
{
	int	quotient;
	int	remainder;

	quotient = 0;
	remainder = 0;
	if (n < 0 && n != -2147483648)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n == -2147483648)
	{
		ft_putnbr_max();
		return ;
	}
	quotient = n / 10;
	if (quotient != 0)
	{
		ft_putnbr(quotient);
	}
	remainder = n % 10;
	ft_putchar(remainder + 48);
}
