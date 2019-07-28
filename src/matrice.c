/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:14:32 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/28 13:40:44 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** matrice_fill() fills the matrice with 1 when it detects a link between two
** rooms.
*/

static int	matrice_fill(t_farm *farm, int **matrice)
{
	t_rooms	*room;
	t_rooms	*room_bis;
	t_links	*links;

	room = farm->rooms;
	while (room != NULL)
	{
		links = room->links;
		while (links != NULL)
		{
			room_bis = farm->rooms;
			while (room_bis != NULL)
			{
				if (ft_strcmp(room_bis->name, links->name) == 0)
					matrice[room->room_id][room_bis->room_id] = 1;
				room_bis = room_bis->next;
			}
			links = links->next;
		}
		room = room->next;
	}
	return (SUCCESS);
}

/*
** matrice_create() creates an int** that references every links of the map.
** Each rows and columns correspond to a room. We fill the matrice by calling
** matrice_fill(). Then we call the algorithm.
*/

int			**matrice_create(t_farm *farm)
{
	int	i;
	int	j;
	int	total_rooms;
	int	**matrice;

	i = 0;
	j = 0;
	total_rooms = farm->total_rooms;
	if (!(matrice = ft_memalloc(sizeof(int*) * total_rooms)))
		return (NULL);
	if (matrice == NULL)
		return (NULL);
	while (i < total_rooms)
	{
		if (!(matrice[i] = ft_memalloc(sizeof(int) * total_rooms)))
			return (NULL);
		if (matrice[i] == NULL)
			return (NULL);
		i++;
	}
	matrice_fill(farm, matrice);
	// TMP
	t_rooms		*tmp;
	tmp = farm->rooms;
	while (tmp)
	{
		printf("%s | ", tmp->name);
		tmp = tmp->next;
	}
	printf("\nmatrice:\n");
	int k, l;
	k = 0;
	while (k < total_rooms)
	{
		l = 0;
		while (l < total_rooms)
		{
			printf("%d ", matrice[k][l]);
			l++;
		}
		printf("\n");
		k++;
	}
	// END TMP
	// Mettre ici la condition pour que le BFS tourne plusieurs fois
	int		y = 1;
	while (y < 4)
	{
		printf("\nlancement numéro %d de l'algo:\n", y);
		if (algo(farm, matrice) == ERROR)
			return (NULL);
		init_paths(farm);
		fill_path(farm);
		free_queue(farm);
		y++;
	}
	// TMP
	printf("\nqueue:\n");
	t_queue	*tmp_queue = farm->queue;
	while (tmp_queue)
	{
		printf("%d ", tmp_queue->id);
		tmp_queue = tmp_queue->next;
	}
	printf("\n");
	t_paths		*tmp1;
	tmp1 = farm->paths;
	int x = 0;
	while (tmp1)
	{
		while(x < tmp1->length)
		{
			printf("%d  ", tmp1->path[x]);
			x++;
		}
		printf("\n");
		tmp1 = tmp1->next;
	}
	// END TMP
	return (matrice);
}
