/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:35:46 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/23 16:57:26 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
static void    free_paths(t_farm *farm)
{
    t_paths *tmp;
    t_paths *new;

    tmp = farm->paths;
    while (tmp)
    {
        new = tmp->next;
        ft_memdel((void**)&tmp->path);
        ft_memdel((void**)&tmp);
        tmp = new;
    }
}
*/

/*
static void    free_queue(t_farm *farm)
{
    t_queue *tmp;
    t_queue *new;

    tmp = farm->queue;
    while (tmp)
    {
        new = tmp->next;
        ft_memdel((void**)&tmp);
        tmp = new;
    }
}
*/

/*
** free_links() free links when they exist.
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
** free_rooms() free rooms when they exist.
*/

void			free_rooms(t_rooms *rooms)
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

void			free_farm(t_farm *farm)
{
	free_rooms(farm->rooms);
	//free_queue(farm);
	//free_paths(farm);
	free(farm);
}
