/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:13:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/25 17:36:11 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** bfs() browses the matrice to see if the room id that we specified in the
** parameters is linked to other rooms. If that is the case, and the room is
** not visited nor reserved, we call init_tmp(). When we have found all the
** links, we call unqueue() to unqueue the room id specified in the parameters.
** When we add the end room, we have finished.
*/

static int	bfs(t_farm *farm, t_rooms *parent, int i)
{
	int		ret;

	while (i < farm->total_rooms)
	{
		if (farm->matrice[parent->room_id][i] == 1)
		{
			if ((ret = add_rooms(farm->all[i], i, farm, parent)) == ERROR \
				|| ret == -2)
				return (ret);
			if (save_block_rooms(farm->all[i], farm, i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	unqueue(farm);
	return (FAILURE);
}

/*
** blocking_room() checks, with the room id we specified in the parameters
** (that corresponds to the last link that was deleted from the queue), that
** this room is linked to an other room. If it is, the linked room is the
** blocking room.
*/

static int	blocking_room(t_farm *farm, int last_valid_room)
{
	int		i;

	i = 0;
	while (i < farm->total_rooms)
	{
		if (farm->matrice[last_valid_room][i] == 1)
		{
			if (farm->all[i]->reserved == 1)
				return (i);
		}
		i++;
	}
	return (i);
}

/*
** fill_queue() adds children rooms tho the queue while there are rooms ids in
** the queue, calling bfs(). If we are stucked, we call blocking_room().
*/

static int	fill_queue(t_farm *farm)
{
	int		check_bfs;
	int		first_of_queue;

	check_bfs = 0;
	while (farm->queue)
	{
		if (farm->all[farm->queue->id])
		{
			first_of_queue = farm->queue->id;
			check_bfs = bfs(farm, farm->all[farm->queue->id], 0);
			if (check_bfs == ERROR)
				return (ERROR);
			if (check_bfs == -2)
				return (-2);
			if (check_bfs == FAILURE && !farm->queue)
				return (blocking_room(farm, first_of_queue));
		}
	}
	return (blocking_room(farm, first_of_queue));
}

/*
** algo() fills the queue starting with start room and its children, calling
** queue(), then calls check_queue() to add rooms to the queue.
*/

int			algo(t_farm *farm)
{
	t_rooms	*tmp_rooms;
	int		ret_fill_queue;

	ret_fill_queue = 0;
	tmp_rooms = farm->start;
	if (queue(farm, tmp_rooms->room_id) == ERROR)
		return (ERROR);
	ret_fill_queue = fill_queue(farm);
	if (ret_fill_queue == ERROR)
		return (ERROR);
	return (ret_fill_queue);
}
