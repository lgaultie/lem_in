/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:29:49 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/25 17:50:08 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** init_tmp() calls queue() to add the room id to the queue. Then it updates
** the informations of the room : it is now visited, have a parent room and a
** layer.
*/

static int	init_tmp(t_rooms *tmp_rooms, t_rooms *parent, t_farm *farm, int i)
{
	if (queue(farm, i) == ERROR)
		return (ERROR);
	tmp_rooms->parent = parent;
	tmp_rooms->visited = 1;
	tmp_rooms->layer = parent->layer + 1;
	return (SUCCESS);
}

/*
** save_block_rooms() save all blocking room to prevent the algo from
** getting lost in deadends without trying to free blocking rooms in paths
*/

int			save_block_rooms(t_rooms *tmp_rooms, t_farm *farm, int i)
{
	if (tmp_rooms->room_id == i \
		&& tmp_rooms->reserved == 1 && tmp_rooms->start_end != 1)
	{
		if (block_queue(farm, i) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
** add_rooms() if returns -2, found a whole path
*/

int			add_rooms(t_rooms *tmp_rooms, int i, t_farm *farm, t_rooms *parent)
{
	if (tmp_rooms->room_id == i && tmp_rooms->visited == 0 \
			&& tmp_rooms->reserved == 0 && tmp_rooms->start_end != 1)
	{
		if (init_tmp(tmp_rooms, parent, farm, i) == ERROR)
			return (ERROR);
		if (tmp_rooms->start_end == 2)
			return (-2);
	}
	return (SUCCESS);
}

/*
** fill_reserved() put the rooms in the path to reserved = 1 and visited = 0,
** except for the start and end rooms.
*/

void		fill_reserved(t_farm *farm)
{
	t_paths	*tmp_paths;
	t_rooms	*tmp_rooms;
	int		i;

	tmp_paths = farm->paths;
	tmp_rooms = farm->rooms;
	while (tmp_paths->next)
		tmp_paths = tmp_paths->next;
	while (tmp_rooms)
	{
		i = 0;
		while (i < tmp_paths->length)
		{
			if (tmp_rooms->room_id == tmp_paths->path[i] \
				&& tmp_rooms->start_end != 1 && tmp_rooms->start_end != 2)
			{
				if (in_released_rooms(farm, tmp_rooms->room_id) == SUCCESS)
					tmp_rooms->to_reserve = 1;
				tmp_rooms->reserved = 1;
			}
			i++;
		}
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
}
