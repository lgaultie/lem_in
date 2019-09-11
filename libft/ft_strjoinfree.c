/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:04:14 by lgaultie          #+#    #+#             */
/*   Updated: 2019/06/21 16:04:28 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int free_who)
{
	size_t	len;
	char	*ret;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ret = (char*)malloc(len * sizeof(char))))
		return (NULL);
	ret = ft_strcpy(ret, s1);
	ret = ft_strcat(ret, s2);
	if (s1 == s2 && free_who == 1)
	{
		free(s1);
		return (ret);
	}
	if (free_who == 1)
		free(s1);
	if (free_who == 2)
		free(s2);
	return (ret);
}
