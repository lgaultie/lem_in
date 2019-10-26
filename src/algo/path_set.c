/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 23:35:40 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/22 23:13:05 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** init_new_path() initializes a new path in the new paths structure.
*/

static int		*init_new_path(t_paths *new_path, int i, t_paths *paths)
{
	if (!(new_path->path = ft_memalloc(sizeof(int) * new_path->length)))
		return (NULL);
	while (i < new_path->length)
	{
		new_path->path[i] = paths->path[i];
		i++;
	}
	return (new_path->path);
}

/*
** init_paths_cpy() copies current paths into a new structure.
*/

static t_paths	*init_paths_cpy(t_paths *paths, t_paths *first_path,
				t_paths *new_path, t_paths *prev_path)
{
	while (paths)
	{
		prev_path = new_path;
		if (!(new_path = ft_memalloc(sizeof(t_paths))))
			return (NULL);
		!first_path ? first_path = new_path : 0;
		if (prev_path)
			prev_path->next = new_path;
		new_path->length = paths->length;
		if (new_path->length > 0)
			new_path->path = init_new_path(new_path, 0, paths);
		new_path->prev = prev_path;
		new_path->next = NULL;
		paths = paths->next;
	}
	return (first_path);
}

/*
** save_path() and save_path2() save in the sets structure the paths
** combinations, in an incremental order, then counts the number of rooms in
** each set, then calls replace_or_delete().
*/

void			save_path2(t_farm *farm, t_paths *paths, int i, int j)
{
	t_paths	*paths_on_set;
	t_paths	*paths_cpy;
	t_paths	*tmp_paths_cpy;

	paths_cpy = init_paths_cpy(paths, NULL, NULL, NULL);
	if ((paths_on_set = farm->last_set->paths) == NULL)
		farm->last_set->paths = paths_cpy;
	else
	{
		paths_on_set = farm->last_set->paths;
		while (paths_on_set)
		{
			i += paths_on_set->length;
			paths_on_set = paths_on_set->next;
		}
		tmp_paths_cpy = paths_cpy;
		while (tmp_paths_cpy)
		{
			j += tmp_paths_cpy->length;
			tmp_paths_cpy = tmp_paths_cpy->next;
		}
		replace_or_delete(i, j, farm, paths_cpy);
	}
}

int				save_path(t_farm *farm, t_paths *paths)
{
	t_sets	*tmp_sets;
	int		h;

	h = 0;
	if (farm->nb_paths <= 0)
		return (SUCCESS);
	tmp_sets = farm->sets;
	while (h < farm->nb_paths - 1)
	{
		tmp_sets = tmp_sets->next;
		h++;
	}
	farm->last_set = tmp_sets;
	save_path2(farm, paths, 0, 0);
	return (SUCCESS);
}
