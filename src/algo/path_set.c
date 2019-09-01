/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 23:35:40 by cmouele           #+#    #+#             */
/*   Updated: 2019/08/29 18:25:32 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** init_paths_cpy() copies current paths into a new structure.
*/

static int	init_paths_cpy(t_paths *paths, t_paths **paths_cpy)
{
	t_paths	*new_path;
	t_paths	*prev_path;
	int		i;

	ft_putstr("in init_save_path()\n");
	new_path = NULL;
	while (paths)
	{
		prev_path = new_path;
		if ((new_path = ft_memalloc(sizeof(t_paths))) == NULL)
			return (ERROR);
		if (prev_path)
			prev_path->next = new_path;
		else
			*paths_cpy = new_path;
		new_path->length = paths->length;
		if (new_path->length > 0)
		{
			if ((new_path->path = ft_memalloc(sizeof(int) * new_path->length)) == NULL)
				return (ERROR);
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
	return (SUCCESS);
}

/*
** delete_set() frees and deletes the set of path we want to replace.
*/

void	delete_set(t_farm *farm, t_paths *paths_on_set)
{
	t_paths	*tmp;
	t_paths	*new;
	int		i;

	i = 0;
	tmp = paths_on_set;
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
	farm->all_paths[farm->nb_paths - 1] = NULL;
}

/*
** save_path() saves in an array of paths the paths combinations, in an
** incremental order. If we have 2 sets that have the same number of paths, we
** compare them and keep the set that has the lower number of rooms.
*/

int			save_path(t_farm *farm, t_paths *paths)
{
	t_paths	*paths_on_set;
	t_paths	*paths_cpy;
	t_paths	*tmp_paths_cpy;
	int		i;
	int		j;

	if (farm->nb_paths <= 0)
		return (SUCCESS);
	paths_cpy = NULL;
	if (init_paths_cpy(paths, &paths_cpy) == ERROR)
		return (ERROR);
	paths_on_set = farm->all_paths[farm->nb_paths - 1];
	i = 0;
	j = 0;
	if (paths_on_set == NULL)
	{
		farm->all_paths[farm->nb_paths - 1] = paths_cpy;
		print_tab_paths(farm); // TMP
	}
	else
	{
		paths_on_set = farm->all_paths[farm->nb_paths - 1];
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
			ft_putstr("on supprime le set\n");
			delete_set(farm, farm->all_paths[farm->nb_paths - 1]);
			farm->all_paths[farm->nb_paths - 1] = paths_cpy;
			print_tab_paths(farm); // TMP
		}
	}
	return (SUCCESS);
}
