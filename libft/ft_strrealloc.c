/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:14:59 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/16 15:06:26 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrealloc(char *str, int len)
{
	char	*newstr;

	if (!(newstr = malloc(sizeof(char) * (ft_strlen(str) + len + 1))))
		return (NULL);
	ft_bzero(newstr, ft_strlen(str) + len + 1);
	ft_strcpy(newstr, str);
	return (newstr);
}
