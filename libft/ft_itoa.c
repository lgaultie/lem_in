/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:26:48 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/19 17:33:01 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_sign_n(int n_sign)
{
	if (n_sign < 0)
		n_sign = n_sign * -1;
	return (n_sign);
}

static int		ft_size_n(int n_size)
{
	int	count_int;

	count_int = 1;
	if (n_size < 0)
		count_int++;
	while (n_size / 10 != 0)
	{
		n_size = n_size / 10;
		count_int++;
	}
	return (count_int);
}

static char		*ft_allocate(int n, int count_int, int n_quotient, int n_remain)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * (count_int + 1));
	if (str == NULL)
		return (NULL);
	str[count_int] = '\0';
	count_int--;
	while (count_int >= 0)
	{
		if (count_int == 0 && n < 0)
			str[count_int] = '-';
		else
		{
			n_quotient = n_quotient / 10;
			n_remain = n_remain % 10;
			str[count_int] = n_remain + '0';
			n_remain = n_quotient;
		}
		count_int--;
	}
	return (str);
}

static char		*ft_allocate_minint(void)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 12);
	if (str == NULL)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		count_int;
	int		n_quotient;
	int		n_remain;

	count_int = ft_size_n(n);
	n_quotient = ft_sign_n(n);
	n_remain = ft_sign_n(n);
	if (n == -2147483648)
		str = ft_allocate_minint();
	else
		str = ft_allocate(n, count_int, n_quotient, n_remain);
	return (str);
}
