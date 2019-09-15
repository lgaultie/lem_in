/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 10:38:28 by cmouele           #+#    #+#             */
/*   Updated: 2018/11/22 10:42:54 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	count;

	count = 0;
	if (s && f)
	{
		while (s[count] != '\0')
		{
			f(count, &s[count]);
			count++;
		}
	}
}
