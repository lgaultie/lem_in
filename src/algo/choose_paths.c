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

/*
** unvisit_rooms() checks all the rooms and set their `visited` attribute to 0.
*/

static void	unvisit_rooms(t_farm *farm)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
}

/*
** check_last_path() adds the last path found in paths structure, and checks if
** it is the same as the other paths. If true, we have found all the paths
** possible, and we no longer need to call our algorithm. We delete the last
** path found.
*/

static int	check_last_path(t_farm *farm)
{
	t_paths	*tmp_path;
	t_paths	*tmp_path2;
	t_paths	*last_path;
	int		i;

	printf("check last path\n");
	if (init_paths(farm) == ERROR || fill_path(farm) == ERROR)
		return (ERROR);
	free_queue(farm);
	fill_reserved(farm);
	tmp_path = farm->paths;
	tmp_path2 = farm->paths;
	while (tmp_path->next)
		tmp_path = tmp_path->next;
	last_path = tmp_path;
	while (tmp_path2)
	{
		if (tmp_path2->length == last_path->length)
		{
			i = 0;
			while (i < last_path->length)
			{
				if (tmp_path2->path[i] != last_path->path[i])
					return (FAILURE);
				if (i == (last_path->length - 1))
				{
					printf("There are 2 similar paths, delete the last one\n");
					delete_path(farm, last_path);
					return (SUCCESS);
				}
				i++;
			}
		}
		tmp_path2 = tmp_path2->next;
	}
	return (FAILURE);
}

/*
** choose_best_paths() calls algo() and checks what it returns.
** If it returns 0, we are at the end or we are jammed. If we are stucked, we
** call backtrack_paths() to unreserve a room. The next occurence of algo()
** will call path_to_delete() to delete the path where the unreserved room was.
** Else, we found a path, and call init_path(), fill_path() and fill_reserved()
** to register it.
*/

int			choose_best_paths(t_farm *farm, int **matrice)
{
	int		ret_algo;
	int		ret_backtrack;
	int		ret_last_path;

	ret_backtrack = -1;
	while (1)
	{
		while ((ret_algo = algo(farm, matrice)) == -2)
		{
			printf("in while algo\n");
			if (ret_backtrack != -1)
			{
				ret_last_path = check_last_path(farm);
				if (ret_last_path == SUCCESS)
					return (SUCCESS);
				if (ret_last_path == ERROR)
					return (ERROR);
				path_to_delete(farm, ret_backtrack);
				ret_backtrack = -1;
			}
			if (init_paths(farm) == ERROR || fill_path(farm) == ERROR)
				return (ERROR);
			free_queue(farm);
			fill_reserved(farm);
		}
		printf("ret algo = %d\n", ret_algo);
		if (ret_algo != -2)
		{
			unvisit_rooms(farm);
			ret_backtrack = backtrack_paths(ret_algo, farm);
			printf("ret_backtrack: %d\n", ret_backtrack);
			// TMP
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
			// END TMP
			if (ret_backtrack == ERROR)
				return (SUCCESS);
		}
	}
	return (SUCCESS);
}
