/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:14:32 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/02 16:15:48 by lgaultie         ###   ########.fr       */
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

// /*
// ** check_starters()
// */
//
// int			check_starters(t_farm *farm, int **matrice)
// {
// 	t_rooms	*tmp;
// 	t_rooms	*tmp_reserved;
// 	int 	i;
// 	int		nb_links;
// 	int		nb_reserved;
//
// 	ft_putstr("in check_starters()\n");
// 	tmp = farm->rooms;
// 	i = 0;
// 	nb_links = 0;
// 	nb_reserved = 0;
// 	while (tmp->start_end != 1)
// 		tmp = tmp->next;
// 	while (i < farm->total_rooms)
// 	{
// 		if (matrice[tmp->room_id][i] == 1)
// 		{
// 			nb_links++;
// 			tmp_reserved = farm->rooms;
// 			print_free_rooms(farm);
// 			while (tmp_reserved)
// 			{
// 				if (tmp_reserved->room_id == i)
// 				{
// 					if (tmp_reserved->reserved == 1)
// 						nb_reserved++;
// 				}
// 				tmp_reserved = tmp_reserved->next;
// 			}
// 		}
// 		i++;
// 	}
// 	ft_putstr("nb_links : ");
// 	ft_putnbr(nb_links);
// 	ft_putchar('\n');
// 	ft_putstr("nb_reserved : ");
// 	ft_putnbr(nb_reserved);
// 	ft_putchar('\n');
// 	if (nb_links == nb_reserved)
// 	{
// 		// save_path(farm, farm->paths);
// 		print_tab_paths(farm);
// 		print_all_paths(farm);
// 		return (SUCCESS);
// 	}
// 	return (FAILURE);
// }

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
	int		ret_find_path;

	while (farm->paths == NULL || check_paths(farm) == FAILURE)
	{
		if ((ret_find_path = find_paths(farm, matrice)) == ERROR)
			return (NULL);
		if (ret_find_path == FAILURE || ret_find_path == END)
			return (matrice);
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
