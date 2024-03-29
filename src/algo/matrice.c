/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:14:32 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/25 17:55:41 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** matrice_fill() fills the matrice with 1 when it detects a link between two
** rooms.
*/

static int	matrice_fill(t_farm *farm)
{
	t_rooms	*room;
	t_rooms	*room_bis;
	t_links	*links;

	room = farm->rooms;
	while (room)
	{
		links = room->links;
		while (links)
		{
			room_bis = farm->rooms;
			while (room_bis)
			{
				if (room_bis->name[0] - links->name[0] == 0)
				{
					if (ft_strcmp(room_bis->name, links->name) == 0)
						farm->matrice[room->room_id][room_bis->room_id] = 1;
				}
				room_bis = room_bis->next;
			}
			links = links->next;
		}
		room = room->next;
	}
	return (SUCCESS);
}

/*
** matrice_create() creates an int** that references every links of the map.
** Each rows and columns correspond to a room. We fill the matrice by calling
** matrice_fill(). Then we call our algorithm, the function that does a BFS
** until we found two similar paths.
*/

int			**matrice_create(t_farm *farm, int i)
{
	int		total_rooms;
	int		ret_find_path;

	i = 0;
	total_rooms = farm->total_rooms;
	if (!(farm->matrice = ft_memalloc(sizeof(int*) * total_rooms)))
		return (NULL);
	while (i < total_rooms)
	{
		if (!(farm->matrice[i] = ft_memalloc(sizeof(int) * total_rooms)))
			return (NULL);
		i++;
	}
	matrice_fill(farm);
	while (farm->paths == NULL || check_paths(farm) == FAILURE)
	{
		if ((ret_find_path = find_paths(farm, 0, 0)) == ERROR)
			return (NULL);
		if (ret_find_path == DEADEND)
			break ;
		if (ret_find_path == FAILURE)
			return (farm->matrice);
	}
	return (farm->matrice);
}
