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
** check_number_of_paths_found()
*/

static int	check_number_of_paths_found(t_farm *farm)
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
** found_max_paths() checks if we found the exact number of possible paths
** regarding start/end's links. Real number of possible paths may be less.
*/

static int	found_max_paths(t_farm *farm)
{
	int		max_paths;
	int		links_of_start;
	int		links_of_end;
	t_rooms	*tmp_room;

	printf("found max paths\n");
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

/*static int	*save_last_path_found(t_farm *farm)
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
}*/

/*static int	check_new_and_last_path_found(int *last, t_farm *farm)
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
}*/

/*
** choose_best_paths() calls algo() and checks what it returns.
** If it returns 0, we are at the end or we are jammed. If we are jammed, we
** call backtrack_paths() to unreserve a room. The next occurence of algo()
** will call path_to_delete() to delete the path where the unreserved room was.
** Else, we found a path, and call init_path(), fill_path() and fill_reserved()
** to register it.
*/

int			choose_best_paths(t_farm *farm, int **matrice)
{
	int		ret_algo;
	int		ret_backtrack;

	ret_backtrack = -1;
	while (1)
	{
		while ((ret_algo = algo(farm, matrice)) == SUCCESS)
		{
			printf("in while algo\n");
			if (ret_backtrack != -1)
			{
				path_to_delete(farm, ret_backtrack);
				ret_backtrack = -1;
			}
			if (init_paths(farm) == ERROR || fill_path(farm) == ERROR)
				return (ERROR);
			free_queue(farm);
			fill_reserved(farm);
		}
		printf("ret algo = %d\n", ret_algo);
		if (ret_algo == 0)
		{
			unvisit_rooms(farm);
			if (found_max_paths(farm) == SUCCESS)
				return (SUCCESS);
			ret_backtrack = backtrack_paths(farm);
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
