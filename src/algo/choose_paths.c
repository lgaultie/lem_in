/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 11:03:23 by lgaultie          #+#    #+#             */
/*   Updated: 2019/08/04 16:13:52 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		check_number_of_paths_found(t_farm *farm)
{
	t_paths	*tmp;
	int		i;

	tmp = farm->paths;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	printf("on en a trouvé: %d.\n", i);
	return (i);
}

/*
** found_all_paths() : checks if we found the exact number of possible paths
** regarding start/end's links. Real number of possible paths may be less.
*/

int		found_max_paths(t_farm *farm)
{
	int		max_paths;
	int		links_of_start;
	int		links_of_end;
	t_rooms	*tmp_room;

	tmp_room = farm->rooms;
	while (tmp_room)
	{
		if (tmp_room->start_end == 1)
			links_of_start = tmp_room->nb_links;
		if (tmp_room->start_end == 2)
			links_of_end = tmp_room->nb_links;
		tmp_room = tmp_room->next;
	}
	if (links_of_end < links_of_start)
		max_paths = links_of_end;
	else
		max_paths = links_of_start;
	printf("maximum possible de paths: %d et ", max_paths);
	if (check_number_of_paths_found(farm) == max_paths)
		return (SUCCESS);
	return (FAILURE);
}

void		unvisit_rooms(t_farm *farm)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
}

int		*save_last_path_found(t_farm *farm)
{
	int		i;
	t_paths	*tmp;
	int		*ret;

	i = 0;
	tmp = farm->paths;
	while (tmp->next)
		tmp = tmp->next;
	ret = ft_memalloc(sizeof(int) * tmp->length);
	while (i < tmp->length)
	{
		ret[i] = tmp->path[i];
		i++;
	}
	return (ret);
}

int		check_new_and_last_path_found(int *last, t_farm *farm)
{
	int		i;
	t_paths	*tmp;

	i = 0;
	tmp = farm->paths;
	while (tmp->next)
		tmp = tmp->next;
	while (i < tmp->length)
	{
		printf("last[%d] = %d && tmp->path[%d] = %d\n", i, last[i], i, tmp->path[i]);
		if (last[i] != tmp->path[i])
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int		choose_best_paths(t_farm *farm, int **matrice)
{
	int		ret_algo;
	int		ret_backtrack;
	// int		*last_path;

	ret_backtrack = -1;
	while (1)
	// while (found_all_paths(farm) > 0)
	{
		while ((ret_algo = algo(farm, matrice)) == SUCCESS)
		{
			printf("in while\n");
			if (ret_backtrack != -1)
			{
				printf("before delete\n");
				delete_first_path(farm, ret_backtrack);
				ret_backtrack = -1;
			}
			if (init_paths(farm) == ERROR || fill_path(farm) == ERROR)
				return (ERROR);
			free_queue(farm);
			printf("FILLED RESERVED\n\n");
			fill_reserved(farm);
		}
		// last_path = save_last_path_found(farm);
		// if (check_new_and_last_path_found(last_path, farm) == 1)
		// return (SUCCESS);
		printf("ret algo = %d\n", ret_algo);
		if (ret_algo == 0)
		{
			//clean les room visitées par le dernier bfs raté
			unvisit_rooms(farm);
			if (found_max_paths(farm) == SUCCESS)
				return (SUCCESS);
			printf("\nLANCE BATRACK\n");
			ret_backtrack = backtrack_paths(farm);
			printf("ret_backtrack: %d\n", ret_backtrack);


			// t_rooms *tmp = farm->rooms;
			// while (tmp)
			// {
			// 	printf("room id: %d - visited: %d - reserved: %d\n", tmp->room_id, tmp->visited, tmp->reserved);
			// 	tmp = tmp->next;
			// }
			t_paths *tmp = farm->paths;
			printf("\nVOILA MES PATHS: \n");
			{
				while (tmp)
				{
					int x = 0;
					while(x < tmp->length)
					{
						printf("%d ", tmp->path[x]);
						x++;
					}
					printf("\n");
					tmp = tmp->next;
				}
			}
			printf("\n");


			if (ret_backtrack == ERROR)
			{
				printf("BATRACK OVER\n");
				//backtrack n'a aucune salle triple a rendre valide: chemins lineaires tous trouvés
				return (SUCCESS);
			}
		}
	}
	return (SUCCESS);
}
