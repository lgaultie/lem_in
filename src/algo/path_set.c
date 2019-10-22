/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 23:35:40 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/22 16:33:45 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** init_path_cpy_two()
*/

static int		init_paths_cpy_two(t_paths *new_path, t_paths *paths)
{
	int i;

	if (!(new_path->path = ft_memalloc(sizeof(int) * new_path->length)))
		return (ERROR);
	i = 0;
	while (i < new_path->length)
	{
		new_path->path[i] = paths->path[i];
		i++;
	}
	return (SUCCESS);
}

/*
** init_paths_cpy() copies current paths into a new structure.
*/

static t_paths	*init_paths_cpy(t_paths *paths)
{
	t_paths	*first_path;
	t_paths	*new_path;
	t_paths	*prev_path;

	first_path = NULL;
	new_path = NULL;
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
			if (init_paths_cpy_two(new_path, paths) == ERROR)
				return (NULL);
		new_path->prev = prev_path;
		new_path->next = NULL;
		paths = paths->next;
	}
	return (first_path);
}

/*
** delete_set() frees and deletes the set of path we want to replace.
*/

static void		delete_set(t_paths **first_path)
{
	t_paths	*tmp;
	t_paths	*new;
	int		i;

	i = 0;
	tmp = *first_path;
	while (tmp)
	{
		new = tmp->next;
		if (tmp->length > 0)
		{
			while (i < tmp->length)
			{
				ft_memdel((void**)&tmp->path);
				i++;
			}
			i = 0;
		}
		ft_memdel((void**)&tmp);
		tmp = new;
	}
}

/*
** compare_sets() checks if we have 2 sets that have the same number of paths.
** If true, we keep the set that has the lower number of rooms.
*/

static void		compare_sets(t_paths *p_current, t_paths *p_set, t_paths *p_cpy)
{
	int		i;
	int		j;
	t_paths	*tmp_paths_cpy;

	i = 0;
	while (p_set)
	{
		i += p_set->length;
		p_set = p_set->next;
	}
	tmp_paths_cpy = p_cpy;
	j = 0;
	while (tmp_paths_cpy)
	{
		j += tmp_paths_cpy->length;
		tmp_paths_cpy = tmp_paths_cpy->next;
	}
	if (i > j)
	{
		delete_set(&p_current);
		p_current = p_cpy;
	}
	else
		delete_set(&p_cpy);
}

/*
** save_path() saves in the sets structure the paths combinations, in an
** incremental order, then we call compare_sets().
*/

int				save_path(t_farm *farm, t_paths *paths)
{
	t_paths	*paths_on_set;
	t_paths	*paths_cpy;
	t_sets	*tmp_sets;
	int		h;

	if (farm->nb_paths <= 0)
		return (SUCCESS);
	h = 0;
	paths_cpy = init_paths_cpy(paths);
	tmp_sets = farm->sets;
	while (h < farm->nb_paths - 1)
	{
		tmp_sets = tmp_sets->next;
		h++;
	}
	paths_on_set = tmp_sets->paths;
	if (paths_on_set == NULL)
		tmp_sets->paths = paths_cpy;
	else
	{
		paths_on_set = tmp_sets->paths;
		compare_sets(tmp_sets->paths, paths_on_set, paths_cpy);
	}
	return (SUCCESS);
}
