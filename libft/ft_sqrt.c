/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:00:25 by lgaultie          #+#    #+#             */
/*   Updated: 2018/11/23 13:59:35 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int racine;

	racine = 1;
	if (nb < 0)
		return (0);
	while (racine * racine < nb)
		racine++;
	if (racine * racine == nb)
		return (racine);
	return (0);
}
