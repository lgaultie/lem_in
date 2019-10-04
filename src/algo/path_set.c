/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 23:35:40 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/04 12:25:31 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** init_paths_cpy() copies current paths into a new structure.
*/

static t_paths	*init_paths_cpy(t_paths *paths)
{
	t_paths	*first_path;
	t_paths	*new_path;
	t_paths	*prev_path;
	int		i;

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
		{
			if (!(new_path->path = ft_memalloc(sizeof(int) * new_path->length)))
				return (NULL);
			i = 0;
			while (i < new_path->length)
			{
				new_path->path[i] = paths->path[i];
				i++;
			}
		}
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
** save_path() saves in an array of paths the paths combinations, in an
** incremental order. If we have 2 sets that have the same number of paths, we
** compare them and keep the set that has the lower number of rooms.
*/

int				save_path(t_farm *farm, t_paths *paths)
{
	t_paths	*paths_on_set;
	t_paths	*paths_cpy;
	t_paths	*tmp_paths_cpy;
	int		i;
	int		j;

	if (farm->nb_paths <= 0)
		return (SUCCESS);
	paths_cpy = init_paths_cpy(paths);
	paths_on_set = farm->sets[farm->nb_paths - 1];
	i = 0;
	j = 0;
	if (paths_on_set == NULL)
		farm->sets[farm->nb_paths - 1] = paths_cpy;
	else
	{
		paths_on_set = farm->sets[farm->nb_paths - 1];
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
		if (i > j)
		{
			delete_set(&farm->sets[farm->nb_paths - 1]);
			farm->sets[farm->nb_paths - 1] = paths_cpy;
		}
		else
			delete_set(&paths_cpy);
	}
	return (SUCCESS);
}
