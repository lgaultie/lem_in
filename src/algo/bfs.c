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
					printf("room to queue: %d\n", tmp_rooms->room_id);
					if (queue(farm, i) == ERROR)
						return (ERROR);
					tmp_rooms->parent = parent_room;
					tmp_rooms->visited = 1;
					tmp_rooms->layer = parent_room->layer + 1;
					if (tmp_rooms->start_end == 2)
						return (-2); // au lieu de SUCCESS
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
** find_blocking_room()
*/

int		find_blocking_room(t_farm *farm, int **matrice)
{
	t_queue	*tmp_q;
	int		id_last_valid_room;
	int		i;
	t_rooms	*tmp_rooms;

	i = 0;
	tmp_q = farm->queue;
	while (tmp_q->next)
		tmp_q = tmp_q->next;
	id_last_valid_room = tmp_q->id;
	while (i < farm->total_rooms)
	{
		if (matrice[id_last_valid_room][i] == 1)
		{
			tmp_rooms = farm->rooms;
			while (tmp_rooms)
			{
				// printf("on parcours dans find blocking room = %d\n", tmp_rooms->room_id);
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
** check_queue() add children rooms tho the queue while there are rooms ids in
** the queue, calling bfs(). If we are stucked, we call find_blocking_room().
*/

static int	check_queue(t_farm *farm, int **matrice)
{
	t_queue	*tmp_queue;
	t_rooms	*tmp_rooms;
	int check_bfs;

	check_bfs = 0;
	tmp_queue = farm->queue;
	while (tmp_queue)
	{
		tmp_rooms = farm->rooms;
		while (tmp_rooms)
		{
			if (tmp_rooms->room_id == tmp_queue->id)
			{
				check_bfs = bfs(farm, matrice, tmp_rooms);
				if (check_bfs == ERROR)
					return (ERROR);
				else if (check_bfs == -2)	//au lieu de success
					return (-2);
					tmp_queue = farm->queue;
			}
			tmp_rooms = tmp_rooms->next;
		}
		tmp_queue = tmp_queue->next;
	}
	return (find_blocking_room(farm, matrice));
	// return (FAILURE);
}

/*
** algo() fills the queue starting with start room and its children, calling
** queue() and bfs(), then calls check_queue() to add rooms to the queue.
*/

int		algo(t_farm *farm, int **matrice)
{
	t_rooms	*tmp_rooms;
	int		ret;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->start_end == 1)
		{
			printf("queue room algo: %s - id: %d\n", tmp_rooms->name, tmp_rooms->room_id);
			if (queue(farm, tmp_rooms->room_id) == ERROR \
			|| bfs(farm, matrice, tmp_rooms) == ERROR)
				return (ERROR);
			break ;
		}
		tmp_rooms = tmp_rooms->next;
	}
	ret = check_queue(farm, matrice);
	printf("algo renvoie %d\n", ret);
	if (ret == ERROR)
		return (ERROR);
	// if (ret == FAILURE)
	// 	return (FAILURE);
	return (ret);		//au lieu de SUCCESS
}
