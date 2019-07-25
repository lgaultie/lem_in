/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:13:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/25 12:21:30 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	unqueue(t_farm *farm)
{
	t_queue	*tmp_queue;

	tmp_queue = farm->queue;
	map->queue = farm->queue->next;
	free(tmp_queue);
	return (SUCCESS);
}

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
	// farm->queue->id = farm->rooms->room_id;
	// farm->queue->next = NULL;
	new->next = NULL;
	return (SUCCESS);
}

static int	inversed_bfs(t_farm *farm, int **matrice, t_rooms *parent_room)
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
				if (tmp_rooms->room_id == i && tmp_rooms->visited == 0 && tmp_rooms->start_end != 1)
				{
					printf("queue room: %s - id: %d\n", tmp_rooms->name, tmp_rooms->room_id);
					if (queue(farm, i) == ERROR)
						return (ERROR);
					tmp_rooms->parent = parent_room;
					printf("parent room: %s\n", tmp_rooms->parent->name);
					printf("child room: %s\n", tmp_rooms->name);
					tmp_rooms->visited = 1;
					//mtmp_rooms->reserved = 1;
					tmp_rooms->layer = parent_room->layer + 1;
				}
				tmp_rooms = tmp_rooms->next;
			}
		}
		i++;
	}
	printf("unqueue room: %s - id: %d\n", parent_room->name, parent_room->room_id);
	unqueue(farm);
	return (SUCCESS);
}

static int	check_queue(t_farm *farm, int **matrice)
{
	t_queue	*tmp_queue;
	t_rooms	*tmp_rooms;

	tmp_queue = farm->queue;
	while (tmp_queue)
	{
		tmp_rooms = farm->rooms;
		while (tmp_rooms)
		{
			if (tmp_rooms->room_nb == tmp_queue->id)
				if (inversed_bfs(farm, matrice, tmp_rooms) == ERROR)
					return (ERROR);
			tmp_rooms = tmp_rooms->next;
		}
		tmp_queue = tmp_queue->next;
	}
	return (SUCCESS);
}

int			algo(t_farm *farm, int **matrice)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->start_end == 1)
		{
			printf("queue room: %s - id: %d\n", tmp_rooms->name, tmp_rooms->room_id);
			if (queue(farm, tmp_rooms->room_id) == ERROR \
			|| inversed_bfs(farm, matrice, tmp_rooms) == ERROR)
				return (ERROR);
			break ;
		}
		tmp_rooms = tmp_rooms->next;
	}
	if (check_queue(farm, matrice) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
