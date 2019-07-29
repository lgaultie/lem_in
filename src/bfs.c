/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:13:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/28 13:57:37 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	unqueue(t_farm *farm)
{
	t_queue	*tmp_queue;

	tmp_queue = farm->queue;
	farm->queue = farm->queue->next;
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
	new->next = NULL;
	return (SUCCESS);
}

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
					printf("queue room: %s - id: %d - nb of links: %d - parent %d\n", tmp_rooms->name, tmp_rooms->room_id, tmp_rooms->nb_links, parent_room->room_id);
					if (queue(farm, i) == ERROR)
						return (ERROR);
					tmp_rooms->parent = parent_room;
					tmp_rooms->visited = 1;
					tmp_rooms->layer = parent_room->layer + 1;
					if (tmp_rooms->start_end == 2)
						return (FAILURE);
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
	int check_bfs;

	tmp_queue = farm->queue;
	check_bfs = 0;
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
				else if (check_bfs == FAILURE)
					return (SUCCESS);
			}
			tmp_rooms = tmp_rooms->next;
		}
		tmp_queue = tmp_queue->next;
	}
	return (SUCCESS);
}

int		algo(t_farm *farm, int **matrice)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->start_end == 1)
		{
			printf("queue room: %s - id: %d - nb of links: %d\n", tmp_rooms->name, tmp_rooms->room_id, tmp_rooms->nb_links);
			if (queue(farm, tmp_rooms->room_id) == ERROR \
			|| bfs(farm, matrice, tmp_rooms) == ERROR)
				return (ERROR);
			break ;
		}
		tmp_rooms = tmp_rooms->next;
	}
	if (check_queue(farm, matrice) == ERROR)
		return (ERROR);
	//si queue = 0: il n'y a pas de chemin, relancer le BFS en dé-rèservant les salles
	//si queue = 0: il n'y a pas de chemin, relancer le BFS en dé-rèservant les salles
	/*if (farm->queue->next == NULL && farm->queue->id == 0)
	{
		if (set_room_to_unvisited(farm) == ERROR)
			return (ERROR);
		algo(farm, matrice);
	}*/
	return (SUCCESS);
}
