/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:24:12 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/19 08:24:35 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int	count;

	if (s)
	{
		count = 0;
		while (s[count] != '\0')
		{
			ft_putchar_fd(s[count], fd);
			count++;
		}
	}
}
