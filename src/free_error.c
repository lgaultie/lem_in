/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 12:15:48 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/19 12:20:26 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void			free_farm_error(t_farm *farm)
{
	free_rooms(farm->rooms);
	free(farm);
}

int			free_tab_error(char **links)
{
	ft_free_tab(links);
	return (ERROR);
}
