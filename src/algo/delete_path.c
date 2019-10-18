/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christel <christel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:55:11 by christel          #+#    #+#             */
/*   Updated: 2019/10/17 15:48:50 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** delete_path() deletes a path from its source list.
*/

void    delete_path(t_sets *set, t_paths **src, t_paths *path)
{
	t_paths	*tmp;

	if (path->prev == NULL)
	{
		tmp = path->next;
		ft_memdel((void**)&path->path);
		ft_memdel((void**)&path);
		path = tmp;
		path->prev = NULL;
		*src = path;
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
	if (set)
		(set->size)--;
}

/*
** path_to_delete() finds the path(s) that use(s) the room given in parameter,
** and calls unvisit_rooms() and delete_path().
*/

int		path_to_delete(t_farm *farm, int id_room)
{
	t_paths	*tmp;
	int		i;

	tmp = farm->paths;
	while (tmp)
	{
		i = 0;
		while (i < tmp->length)
		{
			if (tmp->path[i] == id_room)
			{
				unvisit(tmp->path, tmp->length, farm, id_room);
				delete_path(NULL, &(farm->paths), tmp);
				farm->nb_paths--;
				tmp = farm->paths;
				return (SUCCESS);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
