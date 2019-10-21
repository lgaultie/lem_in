/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:25 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/17 16:17:26 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** in_released_rooms() checks if the room_id provided is in
** farm->released_rooms array.
*/

int			in_released_rooms(t_farm *farm, int id)
{
	int	i;

	i = 0;
	while (i < farm->size_released)
	{
		if (farm->released_rooms[i] == id)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

/*
** release_rooms_on_same_path() put visited = 0 and reserved = 0 to the rooms
** that are on the same path that the room id provided in the parameters.
*/

static void	release_rooms_on_same_path(t_farm *farm, t_paths *path, int id)
{
	int		i;
	int		j;

	i = 0;
	while (i++ < path->length)
	{
		if (path->path[i] == id)
		{
			farm->size_released = path->length;
			if (!(farm->released_rooms = ft_memalloc(sizeof(int) * farm->size_released)))
				return ;
			j = 0;
			while (--i > 0)
			{
				if (i > 0)
				{
					farm->released_rooms[j] = path->path[i];
					j++;
					farm->all_rooms[path->path[i]]->visited = 0;
					farm->all_rooms[path->path[i]]->reserved = 0;
				}
			}
			break ;
		}
	}
}

/*
** backtrack_paths() goes too the room id given in parameters, and set its
** visited and reserved to 0, then it calls release_rooms_on_the_same_path()
** before returning the room id.
*/

int			backtrack_paths(int room_to_deal, t_farm *farm)
{
	t_rooms	*tmp_rooms;
	t_paths	*tmp_paths;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->room_id == room_to_deal && tmp_rooms->start_end != 2)
		{
			tmp_rooms->visited = 0;
			tmp_rooms->reserved = 0;
			tmp_paths = farm->paths;
			while (tmp_paths)
			{
				free(farm->released_rooms);
				release_rooms_on_same_path(farm, tmp_paths, room_to_deal);
				tmp_paths = tmp_paths->next;
			}
			return (tmp_rooms->room_id);
		}
		tmp_rooms = tmp_rooms->next;
	}
	return (ERROR);
}
