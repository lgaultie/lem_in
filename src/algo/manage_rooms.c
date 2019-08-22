/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:25 by lgaultie          #+#    #+#             */
/*   Updated: 2019/08/21 16:07:02 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** fill_reserved() put the rooms in the path to reserved = 1, except for the
** start and end rooms, and to visited = 0.
*/

int		fill_reserved(t_farm *farm)
{
	t_paths	*tmp_paths;
	t_rooms	*tmp_rooms;
	int		i;

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
				tmp_rooms->reserved = 1;
			i++;
		}
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
	return (SUCCESS);
}

/*
** backtrack_paths() goes too the room id given in parameters, and set its
** visited and reserved to 0 before returning the room id.
*/

int		backtrack_paths(int room_to_deal, t_farm *farm)
{
	t_rooms		*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->room_id == room_to_deal && tmp_rooms->start_end != 2)
		{
			tmp_rooms->visited = 0;
			tmp_rooms->reserved = 0;
			return (tmp_rooms->room_id);
		}
		tmp_rooms = tmp_rooms->next;
	}
	return (ERROR);
}

/*
** delete_path() deletes the path from paths structure.
*/

void	delete_path(t_farm *farm, t_paths *path)
{
	t_paths	*tmp;
	int		i;

	i = 0;
	// TMP
	ft_putstr("On delete le path: ");
	while (i < path->length)
	{
		ft_putnbr(path->path[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	// END TMP
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
	// TMP
	t_paths		*tmp_path;
	tmp_path = farm->paths;
	ft_putchar('\n');
	while (tmp_path)
	{
		ft_putstr("PATHS EN COURS APRES DELETE : ");
		int x = 0;
		while(x < tmp_path->length)
		{
			ft_putnbr(tmp_path->path[x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		tmp_path = tmp_path->next;
	}
	ft_putchar('\n');
	// END TMP
}