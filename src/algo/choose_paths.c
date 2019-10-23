/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 11:03:23 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/23 18:22:39 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

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
** backtrack_error() if bactrack_error returns error, it couldn't find the
** blocking room, if may be a dead end or another error.
*/

static int	backtrack_error(t_farm *farm)
{
	if (farm->nb_paths > 0)
	{
		return (DEADEND);
	}
	return (ERROR);
}

static void	free_and_fill(t_farm *farm)
{
	free_queue(farm);
	fill_reserved(farm);
}

/*
** find_paths() calls algo() and checks what it returns.
** If it returns -2, we found the end room, so our BFS is complete. We save the
** path in our structure and reserve the rooms.
** If it returns another number (a room id), it means we are stucked here. We
** call backtrack_paths() to unreserve the room.
*/

int			find_paths(t_farm *farm, int ret_algo, int fill,
			int delete, int to_delete)
{
	static int	ret_backtrack = -1;
	static int	just_deleted = -1;

	if (delete == 1)
		ret_backtrack = to_delete;
	while ((ret_algo = algo(farm)) == -2)
	{
		if (init_paths(farm) == ERROR || ((fill = fill_path(farm)) == ERROR))
			return (ERROR);
		if (fill == FAILURE)
			return (FAILURE);
		free_and_fill(farm);
		if (ret_backtrack != -1)
		{
			path_to_delete(farm, ret_backtrack);
			ret_backtrack = -1;
			just_deleted = 1;
		}
		if (just_deleted != 1)
			if (save_path(farm, farm->paths) == ERROR)
				return (ERROR);
		just_deleted = -1;
	}
	delete = 0;
	if (ret_algo != -2)
	{
		if ((ret_backtrack = backtrack_paths(ret_algo, farm)) == ERROR)
			return (backtrack_error(farm));
	}
	return (SUCCESS);
}
