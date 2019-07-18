/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:35:46 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/18 19:31:00 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** free_links() free les links quand ils existent.
*/

static void		free_links(t_links *links)
{
	t_links		*tmp;

	while (links->next)
	{
		tmp = links;
		links = links->next;
		free(tmp->name);
		free(tmp);
	}
	if (!(links->next))
	{
		free(links->name);
		free(links);
	}
}

/*
** free_rooms() free les rooms quand elles existent.
*/

static void		free_rooms(t_rooms *rooms)
{
	t_rooms		*tmp;

	while (rooms)
	{
		if (rooms->links)
			free_links(rooms->links);
		tmp = rooms;
		rooms = rooms->next;
		free(tmp->name);
		free(tmp);
	}
}

void            free_farm(t_farm *farm)
{
    free_rooms(farm->rooms);
    free(farm);
}
