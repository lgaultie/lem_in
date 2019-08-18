/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:13:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/31 17:15:25 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** unqueue() removes room id from the queue.
*/

static int	unqueue(t_farm *farm)
{
	t_queue	*tmp_queue;

	tmp_queue = farm->queue;
	farm->queue = farm->queue->next;
	ft_memdel((void**)&tmp_queue);
	return (SUCCESS);
}

/*
** queue() adds room id to the queue.
*/

static int	queue(t_farm *farm, int room_id)
{
	t_queue	*tmp;
	t_queue	*new;

	tmp = farm->queue;
	if (!(new = ft_memalloc(sizeof(t_queue))))
		return (ERROR);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		farm->queue = new;
	new->id = room_id;
	new->next = NULL;
	return (SUCCESS);
}

/*
** bfs() browses the matrice to see if the room id that we specified in the
** parameters is linked to other rooms. If that is the case, and the room is
** not visited nor reserved, we call queue() to add its id to the queue. When
** we have found all the links, we call unqueue() to unqueue the room id
** specified in the parameters. When we add the end room, we have finished.
*/

static int	bfs(t_farm *farm, int **matrice, t_rooms *parent_room)
{
	int		i;
	t_rooms	*tmp_rooms;

	i = 0;
	while (i < farm->total_rooms)
	{
		if (matrice[parent_room->room_id][i] == 1)
		{
			tmp_rooms = farm->rooms;
			while (tmp_rooms)
			{
				if (tmp_rooms->room_id == i && tmp_rooms->visited == 0 \
					&& tmp_rooms->reserved == 0 && tmp_rooms->start_end != 1)
				{
					printf("room to queue: %s\n", tmp_rooms->name);
					if (queue(farm, i) == ERROR)
						return (ERROR);
					tmp_rooms->parent = parent_room;
					tmp_rooms->visited = 1;
					tmp_rooms->layer = parent_room->layer + 1;
					if (tmp_rooms->start_end == 2)
						return (-2);
				}
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

static int	blocking_room(t_farm *farm, int **matrice, int last_valid_room)
{
	int		i;
	t_rooms	*tmp_rooms;

	printf("find_blocking room\n");
	i = 0;
	while (i < farm->total_rooms)
	{
		if (matrice[last_valid_room][i] == 1)
		{
			tmp_rooms = farm->rooms;
			while (tmp_rooms)
			{
				if (tmp_rooms->room_id == i && tmp_rooms->reserved == 1)
				{
					printf("room qui bloque = %d\n", tmp_rooms->room_id);
					return (i);
				}
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

static int	fill_queue(t_farm *farm, int **matrice)
{
	t_rooms	*tmp_rooms;
	int 	check_bfs;
	int		first_of_queue;

	printf("fill queue\n");
	check_bfs = 0;
	while (farm->queue)
	{
		tmp_rooms = farm->rooms;
		while (tmp_rooms)
		{
			if (tmp_rooms->room_id == farm->queue->id)
			{
				first_of_queue = farm->queue->id;
				check_bfs = bfs(farm, matrice, tmp_rooms);
				if (check_bfs == ERROR)
					return (ERROR);
				if (check_bfs == -2)
					return (-2);
				if (check_bfs == FAILURE && !farm->queue)
					return (blocking_room(farm, matrice, first_of_queue));
			}
			tmp_rooms = tmp_rooms->next;
		}
	}
	return (blocking_room(farm, matrice, first_of_queue));
}

/*
** algo() fills the queue starting with start room and its children, calling
** queue(), then calls check_queue() to add rooms to the queue.
*/

int		algo(t_farm *farm, int **matrice)
{
	t_rooms	*tmp_rooms;
	int		ret_fill_queue;

	ret_fill_queue = 0;
	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->start_end == 1)
		{
			printf("room to queue: %s\n", tmp_rooms->name);
			if (queue(farm, tmp_rooms->room_id) == ERROR)
				return (ERROR);
			ret_fill_queue = fill_queue(farm, matrice);
			if (ret_fill_queue == ERROR)
				return (ERROR);
			break ;
		}
		tmp_rooms = tmp_rooms->next;
	}
	return (ret_fill_queue);
}
