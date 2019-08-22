/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:14:32 by lgaultie          #+#    #+#             */
/*   Updated: 2019/08/21 15:49:05 by lgaultie         ###   ########.fr       */
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
** matrice_fill(). Then we call our algorithm, the function that does a BFS
** until we found two similar paths.
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
	while (i < total_rooms)
	{
		if (!(matrice[i] = ft_memalloc(sizeof(int) * total_rooms)))
			return (NULL);
		i++;
	}
	matrice_fill(farm, matrice);
	// TMP
	ft_putstr("\nmatrice:\n");
	int k, l;
	k = 0;
	while (k < total_rooms)
	{
		l = 0;
		while (l < total_rooms)
		{
			ft_putnbr(matrice[k][l]);
			ft_putchar(' ');
			l++;
		}
		ft_putchar('\n');
		k++;
	}
	// END TMP
	while (farm->paths == NULL || check_paths(farm) == FAILURE)
	{
		if (find_paths(farm, matrice) == ERROR)
			return (NULL);
	}
	// TMP
	t_paths		*tmp_path;
	tmp_path = farm->paths;
	ft_putchar('\n');
	while (tmp_path)
	{
		ft_putstr("path: ");
		int x = 0;
		while(x < tmp_path->length)
		{
			ft_putnbr(tmp_path->path[x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		tmp_path = tmp_path->next;
	}
	// END TMP
	return (matrice);
}
