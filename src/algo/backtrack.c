/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:25 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/22 18:03:56 by lgaultie         ###   ########.fr       */
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

static int	release(int i, t_farm *farm, t_paths *tmp)
{
	int		j;

	j = 0;
	i--;
	if (i > 0)
	{
		farm->release[j] = tmp->path[i];
		j++;
		farm->all_rooms[tmp->path[i]]->visited = 0;
		farm->all_rooms[tmp->path[i]]->reserved = 0;
	}
	return (i);
}

/*
** release_rooms_on_same_path() put visited = 0 and reserved = 0 to the rooms
** that are on the same path that the room id provided in the parameters.
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
				while (i > 0)
					i = release(i, farm, tmp);
				break ;
			}
			i++;
		}
		tmp = tmp->next;
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
	return (ERROR);
}
