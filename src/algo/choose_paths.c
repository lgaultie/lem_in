/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 11:03:23 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/22 15:14:47 by lgaultie         ###   ########.fr       */
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
** check_paths() checks if we have two similar paths in our paths structure.
** If this is the case, we have found all the paths possible, and we no longer
** need to call our algorithm. We delete the first similar path.
*/

int			check_paths(t_farm *farm)
{
	int		j;
	t_paths	*path;
	t_paths	*all_paths;

	path = farm->paths;
	while (path->next)
		path = path->next;
	all_paths = farm->found_paths;
	while (all_paths->next)
	{
		j = 0;
		if (path->length == all_paths->length)
		{
			while (j < path->length && path->path[j] == all_paths->path[j])
				j++;
			if (j == path->length)
			{
				delete_path(NULL, &(farm->paths), path);
				save_path(farm, farm->paths);
				return (SUCCESS);
			}
		}
		all_paths = all_paths->next;
	}
	return (FAILURE);
}

/*
** end_room() means that our BFS is complete. We save the path in our structure
** and reserve the rooms.
*/

static int	end_room(t_farm *farm, int *ret_backtrack, int *just_deleted)
{
	int	ret_fill;

	if (init_paths(farm) == ERROR || ((ret_fill = fill_path(farm)) == ERROR))
		return (ERROR);
	if (ret_fill == FAILURE)
		return (FAILURE);
	free_queue(farm);
	fill_reserved(farm);
	if (*ret_backtrack != -1)
	{
		path_to_delete(farm, *ret_backtrack);
		*ret_backtrack = -1;
		*just_deleted = 1;
	}
	if (*just_deleted != 1)
	{
		if (save_path(farm, farm->paths) == ERROR)
			return (ERROR);
	}
	*just_deleted = -1;
	return (SUCCESS);
}

/*
** find_paths() calls algo() and checks what it returns.
** If it returns -2, we found the end room, so we call end_room().
** If it returns another number (a room id), it means we are stucked here. We
** call backtrack_paths() to unreserve the room.
*/

int			find_paths(t_farm *farm, int **matrice)
{
	int	ret_algo;
	int	ret_backtrack;
	int	just_deleted;

	ret_backtrack = -1;
	just_deleted = -1;
	while ((ret_algo = algo(farm, matrice)) == -2)
		end_room(farm, &ret_backtrack, &just_deleted);
	if (ret_algo != -2)
	{
		unvisit_rooms(farm);
		ret_backtrack = backtrack_paths(ret_algo, farm);
		if (ret_backtrack == ERROR)
		{
			if (farm->nb_paths > 0)
				return (DEADEND);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
