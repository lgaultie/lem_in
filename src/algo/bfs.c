/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:13:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/23 17:13:17 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <stdio.h>//

/*
** init_tmp() calls queue() to add the room id to the queue. Then it updates
** the informations of the room : it is now visited, have a parent room and a
** layer.
*/

static int	init_tmp(t_rooms *tmp_rooms, t_rooms *parent, t_farm *farm, int i)
{
	if (queue(farm, i) == ERROR)
		return (ERROR);
	// t_queue *q = farm->queue;
	// ft_putstr("queue:\n");
	// while (q)
	// {
	// 	ft_putstr("q id: ");
	// 	ft_putnbr(q->id);
	// 	ft_putchar('\n');
	// 	q = q->next;
	// }
	// ft_putstr("end queue:\n");
	tmp_rooms->parent = parent;
	tmp_rooms->visited = 1;
	tmp_rooms->layer = parent->layer + 1;
	return (SUCCESS);
}

/*
** bfs() browses the matrice to see if the room id that we specified in the
** parameters is linked to other rooms. If that is the case, and the room is
** not visited nor reserved, we call init_tmp(). When we have found all the
** links, we call unqueue() to unqueue the room id specified in the parameters.
** When we add the end room, we have finished.
*/

static int	bfs(t_farm *farm, t_rooms *parent_room, int i)
{
	t_rooms	*tmp_rooms;

	i = 0;
	while (i < farm->total_rooms)
	{
		if (farm->matrice[parent_room->room_id][i] == 1)
		{
			tmp_rooms = farm->rooms;
			while (tmp_rooms)
			{
				if (tmp_rooms->room_id == i && tmp_rooms->visited == 0 \
					&& tmp_rooms->reserved == 0 && tmp_rooms->start_end != 1)
				{
					if (init_tmp(tmp_rooms, parent_room, farm, i) == ERROR)
						return (ERROR);
					if (tmp_rooms->start_end == 2)
						return (-2);
				}
				if (tmp_rooms->room_id == i \
					&& tmp_rooms->reserved == 1 && tmp_rooms->start_end != 1)
					if (block_queue(farm, i) == ERROR)
						return (ERROR);
				tmp_rooms = tmp_rooms->next;
			}
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
	t_rooms	*tmp_rooms;

	i = 0;
	while (i < farm->total_rooms)
	{
		if (farm->matrice[last_valid_room][i] == 1)
		{
			tmp_rooms = farm->rooms;
			while (tmp_rooms)
			{
				if (tmp_rooms->room_id == i && tmp_rooms->reserved == 1)
					return (i);
				tmp_rooms = tmp_rooms->next;
			}
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
	t_rooms	*tmp_rooms;
	int		check_bfs;
	int		first_of_queue;

	check_bfs = 0;
	while (farm->queue)
	{
		tmp_rooms = farm->rooms;
		while (tmp_rooms)
		{
			if (tmp_rooms->room_id == farm->queue->id)
			{
				first_of_queue = farm->queue->id;
				check_bfs = bfs(farm, tmp_rooms, first_of_queue);
				if (check_bfs == ERROR)
					return (ERROR);
				if (check_bfs == -2)
					return (-2);
				if (check_bfs == FAILURE && !farm->queue)
					return (blocking_room(farm, first_of_queue));
			}
			tmp_rooms = tmp_rooms->next;
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
