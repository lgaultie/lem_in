/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:25 by lgaultie          #+#    #+#             */
/*   Updated: 2019/08/04 15:23:04 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** fill_reserved() put the rooms in the path to reserved = 1, except for the
** start and end rooms, and to visited = 0.
*/

int	fill_reserved(t_farm *farm)
{
	t_paths	*tmp_paths;
	t_rooms	*tmp_rooms;
	int		i;

	printf("fill reserved\n");
	tmp_paths = farm->paths;
	tmp_rooms = farm->rooms;
	while (tmp_paths->next)
		tmp_paths = tmp_paths->next;
	while (tmp_rooms)
	{
		i = 0;
		while (i < tmp_paths->length)
		{
			if (tmp_rooms->room_id == tmp_paths->path[i] \
				&& tmp_rooms->start_end != 1 && tmp_rooms->start_end != 2)
			{
				printf("reserve room: %s - id: %d\n", tmp_rooms->name, tmp_rooms->room_id);
				tmp_rooms->reserved = 1;
			}
			i++;
		}
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
	return (SUCCESS);
}

/*
** backtrack_paths() cherche la premiere salle triple réservée, et rend la
** disponible. Retourne le numéro de cette salle pour savoir quel chemin
** supprimer plus tard.
*/

int		backtrack_paths(t_farm *farm)
{
	t_rooms		*tmp_rooms;

	printf("backtrack paths\n");
	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		// printf("room_id = %d, visited = %d, reserved = %d, nb_links = %d\n", tmp_rooms->room_id, tmp_rooms->visited, tmp_rooms->reserved, tmp_rooms->nb_links);
		if (tmp_rooms->reserved == 1 && tmp_rooms->nb_links > 2)
		{
			// printf("je déreserve la premiere salle triple, ici %d\n", tmp_rooms->room_id);
			tmp_rooms->visited = 0;
			tmp_rooms->reserved = 0;
			return (tmp_rooms->room_id);
		}
		tmp_rooms = tmp_rooms->next;
	}
	ft_putstr("pourquoi ya pas de salle triple??\n");
	return (ERROR);
}

/*
** unvisit_rooms() put the rooms of the path to be deleted unvisited, except
** the room corresponding to the id_room given in parameters.
*/

static int	unvisit_rooms(int *path, int length, t_farm *farm, int id_room)
{
	int		i;
	t_rooms	*tmp;

	printf("unvisit rooms\n");
	i = 0;
	tmp = farm->rooms;
	while (tmp && (i < length))
	{
		while (tmp->room_id != path[i])
			tmp = tmp->next;
		if (tmp->room_id == path[i] && tmp->room_id != id_room)
		{
			printf("unvisit room_id %d\n", tmp->room_id);
			tmp->visited = 0;
			tmp->reserved = 0;
		}
		tmp = farm->rooms;
		i++;
	}
	return (SUCCESS);
}

/*
** delete_path() deletes the path from paths structure.
*/

void		delete_path(t_farm *farm, t_paths *path)
{
	t_paths		*tmp;

	printf("delete path\n");
	if (path->prev == NULL)
	{
		tmp = path->next;
		ft_memdel((void**)&path->path);
		ft_memdel((void**)&path);
		path = tmp;
		if (path)
			path->prev = NULL;
		farm->paths = path;
	}
	else
	{
		tmp = path->next;
		if (tmp)
			tmp->prev = path->prev;
		path->prev->next = tmp;
		ft_memdel((void**)&path->path);
		ft_memdel((void**)&path);
	}
}

/*
** path_to_delete() finds the path(s) that use(s) the room given in parameter,
** and calls unvisit_rooms() and delete_path().
*/

int			path_to_delete(t_farm *farm, int id_room)
{
	t_paths		*tmp;
	int			i;

	printf("path to delete\n");
	tmp = farm->paths;
	while (tmp)
	{
		i = 0;
		while (i < tmp->length)
		{
			if (tmp->path[i] == id_room)
			{
				unvisit_rooms(tmp->path, tmp->length, farm, id_room);
				delete_path(farm, tmp);
				return (SUCCESS);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (FAILURE);
}
