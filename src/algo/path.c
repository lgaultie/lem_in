/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:15:36 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/31 14:06:44 by lgaultie         ###   ########.fr       */
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
** find_layer() returns from witch distance the end room is from the start
** room. This will help us know the size of the path.
*/

static int	find_layer(t_farm *farm)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->start_end == 2)
			return (tmp_rooms->layer);
		tmp_rooms = tmp_rooms->next;
	}
	return (SUCCESS);
}

/*
** fill_path() fills a link from the paths structure. It calls find_layer() and
** retrieve_path() to help fill the link.
*/

int			fill_path(t_farm *farm)
{
	t_paths	*tmp_path;
	t_rooms	*tmp_rooms;
	int		layer;

	printf("fill path\n");
	tmp_path = farm->paths;
	tmp_rooms = farm->rooms;
	layer = find_layer(farm);
	while (tmp_path->path)
		tmp_path = tmp_path->next;
	tmp_path->length = layer + 1;
	tmp_path->path = (int*)malloc(sizeof(int) * (layer + 1));
	if (tmp_path->path == NULL)
		return (ERROR);
	while (tmp_rooms)
	{
		if (tmp_rooms->start_end == 2)
			retrieve_path(farm, tmp_path, tmp_rooms->room_id, 0);
		tmp_rooms = tmp_rooms->next;
	}
	return (SUCCESS);
}

/*
** init_paths() creates and initializes a link of the paths structure.
*/

int			init_paths(t_farm *farm)
{
	t_paths	*tmp;
	t_paths	*new;

	printf("init path\n");
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
