/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:14:32 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/30 16:30:14 by lgaultie         ###   ########.fr       */
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
		printf("\nLancement numéro %d de l'algo:\n", y);
		if (algo(farm, matrice) == ERROR || init_paths(farm) == ERROR \
			|| fill_path(farm) == ERROR)
			return (NULL);
		free_queue(farm);
		fill_reserved(farm);
		y++;
	}
	// TMP
	t_paths		*tmp_path;
	tmp_path = farm->paths;
	printf("\n");
	while (tmp_path)
	{
		printf("path: ");
		int x = 0;
		while(x < tmp_path->length)
		{
			printf("%d ", tmp_path->path[x]);
			x++;
		}
		printf("\n\n");
		tmp_path = tmp_path->next;
	}
	// END TMP

	////mise en place du backtrack
	int		id_room = 0;

	if (inspect_paths(farm) == 1)
	{
		id_room = backtrack_paths(farm);
		if (algo(farm, matrice) == ERROR || init_paths(farm) == ERROR \
			|| fill_path(farm) == ERROR)
			return (NULL);
		free_queue(farm);
		fill_reserved(farm);
	}
	if (inspect_paths(farm) == 1)
		delete_first_path(farm, id_room);
	//trouver la condition d'arret de l'algo pour pouvoir relancer autant de
	// fois qu'il faut

	// TMP
	t_paths		*tmp_path1;
	tmp_path1 = farm->paths;
	printf("\n");
	while (tmp_path1)
	{
		printf("path: ");
		int g = 0;
		while(g < tmp_path1->length)
		{
			printf("%d ", tmp_path1->path[g]);
			g++;
		}
		printf("\n\n");
		tmp_path1 = tmp_path1->next;
	}
	// END TMP

	
	return (matrice);
}