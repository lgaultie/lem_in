/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:01:35 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/23 15:19:29 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_final(char *str, int n, int len)
{
	if (n >= 10)
	{
		while (len >= 0)
		{
			str[len - 1] = n % 10 + '0';
			n = n / 10;
			len--;
		}
	}
}

static	void	*ft_number(char *str, int n, int neg, int len)
{
	if (n >= 0 && n < 10)
	{
		if (neg == 1)
		{
			str[0] = '-';
			str[1] = n + '0';
			str[2] = '\0';
			return (str);
		}
		if (neg == 0)
		{
			str[0] = n + '0';
			str[1] = '\0';
			return (str);
		}
	}
	ft_final(str, n, len);
	return (0);
}

static	char	*ft_neg_equal_1(char *s1, int y)
{
	s1[0] = '-';
	s1[y] = '\0';
	return (s1);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;
	int		j;

	neg = 0;
	j = ft_intlen(n);
	len = ft_intlen(n);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n > 2147483647 || n < -2147483648 || n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	if (n >= 0)
		ft_number(str, n, neg, len);
	if (neg == 1)
		ft_neg_equal_1(str, j);
	str[j] = '\0';
	return (str);
}
