/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 12:15:48 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 15:43:15 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** free_farm_error() frees farm and writes an error message.
*/

int	free_farm_error(t_farm *farm)
{
	free_rooms(farm->rooms);
	ft_memdel((void**)&farm);
	ft_putendl(ERROR_MSG);
	return (ERROR);
}

/*
** free_tab_error() frees tab.
*/

int	free_tab_error(char **tab)
{
	ft_free_tab(&tab);
	return (ERROR);
}
