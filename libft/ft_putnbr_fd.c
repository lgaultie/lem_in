/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:25:16 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/19 08:30:09 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_max(int fd)
{
	ft_putchar_fd('-', fd);
	ft_putchar_fd('2', fd);
	ft_putchar_fd('1', fd);
	ft_putchar_fd('4', fd);
	ft_putchar_fd('7', fd);
	ft_putchar_fd('4', fd);
	ft_putchar_fd('8', fd);
	ft_putchar_fd('3', fd);
	ft_putchar_fd('6', fd);
	ft_putchar_fd('4', fd);
	ft_putchar_fd('8', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	int	quotient;
	int	remainder;

	quotient = 0;
	remainder = 0;
	if (n < 0 && n != -2147483648)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n == -2147483648)
	{
		ft_putnbr_max(fd);
		return ;
	}
	quotient = n / 10;
	if (quotient != 0)
	{
		ft_putnbr_fd(quotient, fd);
	}
	remainder = n % 10;
	ft_putchar_fd(remainder + 48, fd);
}
