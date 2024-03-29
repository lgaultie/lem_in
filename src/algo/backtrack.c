/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:25 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/27 16:04:06 by lgaultie         ###   ########.fr       */
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
	while (i < farm->size)
	{
		if (farm->release[i] == id)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

/*
** release() put visited = 0 and reserved = 0.
*/

static int	release(int i, t_farm *farm, t_paths *tmp)
{
	int		j;

	while (i > 0)
	{
		j = 0;
		i--;
		if (i > 0)
		{
			farm->release[j] = tmp->path[i];
			j++;
			farm->all[tmp->path[i]]->visited = 0;
			farm->all[tmp->path[i]]->reserved = 0;
		}
	}
	return (i);
}

/*
** release_rooms_on_same_path() goes to the rooms that are on the same path
** that the room id provided in the parameters, and calls release().
*/

static void	release_rooms_on_same_path(t_farm *farm, int id)
{
	t_paths	*tmp;
	int		i;

	tmp = farm->paths;
	while (tmp)
	{
		i = 0;
		while (i < tmp->length)
		{
			if (tmp->path[i] == id)
			{
				farm->size = tmp->length;
				if (!(farm->release = ft_memalloc(sizeof(int) * farm->size)))
					return ;
				i = release(i, farm, tmp);
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

/*
** unvisit_rooms() checks all the rooms and set their `visited` attribute to 0.
*/

static void	unvisit_rooms(t_farm *farm)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
}

/*
** backtrack_paths() goes too the room id given in parameters, and set its
** visited and reserved to 0, then it calls release_rooms_on_the_same_path()
** before returning the room id, or block_unqueue() and find_paths() if the
** room was in the queue of blocking rooms.
*/

int			backtrack_paths(int room_to_deal, t_farm *farm)
{
	t_rooms	*tmp_rooms;

	unvisit_rooms(farm);
	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->room_id == room_to_deal && tmp_rooms->start_end != 2)
		{
			tmp_rooms->visited = 0;
			tmp_rooms->reserved = 0;
			release_rooms_on_same_path(farm, room_to_deal);
			return (tmp_rooms->room_id);
		}
		tmp_rooms = tmp_rooms->next;
	}
	if (farm->blocking_q)
	{
		farm->all[farm->blocking_q->id]->visited = 0;
		farm->all[farm->blocking_q->id]->reserved = 0;
		block_unqueue(farm);
		if (farm->blocking_q)
			find_paths(farm, 1, farm->blocking_q->id);
	}
	return (ERROR);
}
