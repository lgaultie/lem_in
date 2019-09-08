/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:25 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/04 19:23:42 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		check_if_in_released_rooms(t_farm *farm, int id)
{
	int		i;

	i = 0;
	while (i < farm->size_released)
	{
		if (farm->released_rooms[i] == id)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}


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
				{
					if (check_if_in_released_rooms(farm, tmp_rooms->room_id) == SUCCESS)
					 	tmp_rooms->to_reserve = 1;
					ft_putstr("rend reserved les salles :");
					ft_putnbr(tmp_rooms->room_id);
					ft_putchar('\n');
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
** delete_path() deletes the path from paths structure.
*/

void	delete_path(t_farm *farm, t_paths *path)
{
	t_paths	*tmp;
	int		i;

	i = 0;
	// // TMP
	// ft_putstr("On delete le path: ");
	// while (i < path->length)
	// {
	// 	ft_putnbr(path->path[i]);
	// 	ft_putchar(' ');
	// 	i++;
	// }
	// ft_putchar('\n');
	// // END TMP
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
	// // TMP
	// t_paths		*tmp_path;
	// tmp_path = farm->paths;
	// ft_putchar('\n');
	// while (tmp_path)
	// {
	// 	ft_putstr("PATHS EN COURS APRES DELETE : ");
	// 	int x = 0;
	// 	while(x < tmp_path->length)
	// 	{
	// 		ft_putnbr(tmp_path->path[x]);
	// 		ft_putchar(' ');
	// 		x++;
	// 	}
	// 	ft_putchar('\n');
	// 	tmp_path = tmp_path->next;
	// }
	// ft_putchar('\n');
	// // END TMP
}

/*
** visit_rooms() the blocking room must not be unreserved because it was taken
** for another path, we must do the same with rooms set free during
** release_rooms_on_same_path then taken for another path.
*/

//attention faut pas rendre reserved toutes les salles de la liste
//juste les salles de la liste qui ont ete pris par un chemin ensuite !!!
//jenregistre dans un tableau les salles debloquee avec la salle bloqaunte
//ensuite je regarde ces salles, si elles sont prises dans le tableau
// et quon les mets dans un paths apres, je mets to_reserve a 1
//ensuite ici je met seulement les salles du tableau avec reserve a 1 en
//reserved et visited

void		visit_rooms(t_farm *farm)
{
	int		i;

	i = 0;
	while (i < farm->size_released)
	{
		if (farm->all_rooms[farm->released_rooms[i]]->to_reserve == 1)
		{
			farm->all_rooms[farm->released_rooms[i]]->visited = 1;
			farm->all_rooms[farm->released_rooms[i]]->reserved = 1;
			farm->all_rooms[farm->released_rooms[i]]->to_reserve = 0;
		}
		i++;
	}
	ft_memdel((void**)&farm->released_rooms);
	farm->size_released = 0;
}

/*
** unvisit_rooms() put the rooms of the path to be deleted unvisited, except
** the room corresponding to the id_room given in parameters.
*/

static int	unvisit_rooms(int *path, int length, t_farm *farm, int id_room)
{
	int		i;
	t_rooms	*tmp;

	i = 0;
	tmp = farm->rooms;
	while (tmp && (i < length))
	{
		while (tmp->room_id != path[i])
			tmp = tmp->next;
		if (tmp->room_id == path[i] && tmp->room_id != id_room)
		{
			ft_putstr("path_to_delete rend libre = ");
			ft_putnbr(tmp->room_id);
			ft_putchar('\n');
			tmp->visited = 0;
			tmp->reserved = 0;
		}
		tmp = farm->rooms;
		i++;
	}
	visit_rooms(farm);
	return (SUCCESS);
}

/*
** path_to_delete() finds the path(s) that use(s) the room given in parameter,
** and calls unvisit_rooms() and delete_path().
*/

int			path_to_delete(t_farm *farm, int id_room)
{
	t_paths		*tmp;
	int			i;

	ft_putstr("path to delete, the one with room: ");
	ft_putnbr(id_room);
	ft_putchar('\n');
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

/*
**
*/

void	release_rooms_on_same_path(t_farm *farm, int id)
{
	t_paths		*tmp;
	int			i;
	int			j;

	print_paths(farm);
	tmp = farm->paths;
	while (tmp)
	{
		i = 0;
		while (i < tmp->length)
		{
			if (tmp->path[i] == id)
			{
				farm->size_released = tmp->length;
				if (!(farm->released_rooms = ft_memalloc(sizeof(int) * farm->size_released)))
					return ;
				j = 0;
				while (i > 0)
				{
					i--;
					ft_putstr("rend en non visité les salles: ");
					ft_putnbr(farm->all_rooms[tmp->path[i]]->room_id);
					ft_putchar('\n');
					if (i > 0)
					{
						farm->released_rooms[j] = tmp->path[i];
						j++;
						farm->all_rooms[tmp->path[i]]->visited = 0;
						farm->all_rooms[tmp->path[i]]->reserved = 0;
					}
				}
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	print_free_rooms(farm);
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
			release_rooms_on_same_path(farm, room_to_deal);
			return (tmp_rooms->room_id);
		}
		tmp_rooms = tmp_rooms->next;
	}
	return (ERROR);
}
