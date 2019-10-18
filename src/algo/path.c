/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:15:36 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/17 15:54:03 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** For each room, beginning by the end room, retrieve_path() take the 'parent'
** attribute and add it to the path. Then it calls the function again with the
** room we just added. Until we reach the size of the path, that should
** correspond with the start room.
*/

static int	retrieve_path(t_farm *farm, t_paths *path, int id, int j)
{
	static int	i = 0;
	t_rooms		*tmp_rooms;

	i = j;
	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->room_id == id)
		{
			path->path[i] = tmp_rooms->room_id;
			i++;
			break ;
		}
		tmp_rooms = tmp_rooms->next;
	}
	while (i < path->length)
		retrieve_path(farm, path, tmp_rooms->parent->room_id, i);
	return (SUCCESS);
}

/*
** path_cpy() copies the path found, not to share the same pointer with the
** path in paths structure.
*/

static void	path_cpy(t_paths *new, t_paths *path)
{
	int	i;

	i = 0;
	if (!(new->path = ft_memalloc(sizeof(int) * path->length)))
		return ;
	while (i < path->length)
	{
		new->path[i] = path->path[i];
		i++;
	}
}

/*
** save_found_path() initializes and registers the list of all found paths,
** calling path_cpy().
*/

void		save_found_path(t_farm *farm, t_paths *path)
{
	t_paths	*tmp;
	t_paths	*new;

	tmp = farm->found_paths;
	if ((new = ft_memalloc(sizeof(t_paths))) == NULL)
		return ;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		farm->found_paths = new;
		new->prev = NULL;
	}
	new->next = NULL;
	new->length = path->length;
	path_cpy(new, path);
}

/*
** fill_path() fills a link from the paths structure. It calls find_layer() and
** retrieve_path() to help fill the link, and save_found_path() to save the set
** of paths we found.
*/

int			fill_path(t_farm *farm)
{
	t_paths	*tmp_path;
	t_rooms	*tmp_rooms;
	int		layer;

	tmp_path = farm->paths;
	tmp_rooms = farm->rooms;
	layer = farm->end->layer;
	while (tmp_path->path)
		tmp_path = tmp_path->next;
	tmp_path->length = layer + 1;
	if (!(tmp_path->path = ft_memalloc(sizeof(int) * (layer + 1))))
		return (ERROR);
	retrieve_path(farm, tmp_path, farm->end->room_id, 0);
	save_found_path(farm, tmp_path);
	if (check_paths(farm) == SUCCESS)
		return (FAILURE);
	farm->nb_paths++;
	return (SUCCESS);
}

/*
** init_paths() creates and initializes a link of the paths structure.
*/

int			init_paths(t_farm *farm)
{
	t_paths	*tmp;
	t_paths	*new;

	tmp = farm->paths;
	if ((new = ft_memalloc(sizeof(t_paths))) == NULL)
		return (ERROR);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		farm->paths = new;
		new->prev = NULL;
	}
	new->next = NULL;
	return (SUCCESS);
}
