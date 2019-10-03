/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:14:32 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/03 15:34:47 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** matrice_fill() fills the matrice with 1 when it detects a link between two
** rooms.
*/

static int	matrice_fill(t_farm *farm, int **matrice)
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
				if (ft_strcmp(room_bis->name, links->name) == 0)
					matrice[room->room_id][room_bis->room_id] = 1;
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

int			**matrice_create(t_farm *farm)
{
	int		i;
	int		**matrice;
	int		ret_find_path;

	i = 0;
	if (!(matrice = ft_memalloc(sizeof(int*) * farm->total_rooms)))
		return (NULL);
	while (i < farm->total_rooms)
	{
		if (!(matrice[i] = ft_memalloc(sizeof(int) * farm->total_rooms)))
			return (NULL);
		i++;
	}
	matrice_fill(farm, matrice);
	while (farm->paths == NULL || check_paths(farm) == FAILURE)
	{
		if ((ret_find_path = find_paths(farm, matrice, i, i)) == ERROR)
			return (NULL);
		if (ret_find_path == DEADEND)
			break ;
		if (ret_find_path == FAILURE)
			return (matrice);
	}
	return (matrice);
}
