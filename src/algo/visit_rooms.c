/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visit_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christelle <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:54:40 by christell         #+#    #+#             */
/*   Updated: 2019/09/29 16:54:51 by christell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** visit_rooms() put visited = 1, reserved = 1, and to_reserve = 0 to the rooms
** that are to be reserved in farm->released_rooms. This corresponds to the
** blocking room, and the rooms set free during release_rooms_on_same_path().
*/

static void	visit_rooms(t_farm *farm)
{
	int	i;

	i = 0;
	while (i < farm->size_released)
	{
		if (farm->all_rooms[farm->released_rooms[i]]->to_reserve == 1)
		{
			farm->all_rooms[farm->released_rooms[i]]->visited = 1;
			farm->all_rooms[farm->released_rooms[i]]->reserved = 1;
			farm->all_rooms[farm->released_rooms[i]]->to_reserve = 0;
		}
		i++;
	}
	ft_memdel((void**)&farm->released_rooms);
	farm->size_released = 0;
}

/*
** unvisit() put the rooms of the path to be deleted unvisited, except the room
** corresponding to the id_room given in parameters. Then it calls
** visit_rooms().
*/

int			unvisit(int *path, int length, t_farm *farm, int id_room)
{
	int		i;
	t_rooms	*tmp;

	i = 0;
	tmp = farm->rooms;
	while (tmp && (i < length))
	{
		while (tmp->room_id != path[i])
			tmp = tmp->next;
		if (tmp->room_id == path[i] && tmp->room_id != id_room)
		{
			tmp->visited = 0;
			tmp->reserved = 0;
		}
		tmp = farm->rooms;
		i++;
	}
	visit_rooms(farm);
	return (SUCCESS);
}
