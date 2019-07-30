/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:25 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/30 16:28:01 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int	fill_reserved(t_farm *farm)
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
				printf("reserve room %d\n", tmp_rooms->room_id);
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
** regarde si on a trouvé deux fois le meme path: return (1) si il y a
** deux fois le meme path, return (0) si tous les paths sont différents.
** peut etre vaudrait mieux qu'elle check les deux derniers paths seulement
*/

int		inspect_paths(t_farm *farm)
{
	t_paths		*tmp;
	int			*last;
	int			last_length;
	int			i;
	int			x;

	last_length = 0;
	tmp = farm->paths;
	if (!(last = ft_memalloc(sizeof(int) * tmp->length)))
		return (ERROR);
	while (tmp)
	{
		i = 0;
		x = 0;
		//on regarde si le maillon a le meme path que le dernier
		// printf("last_length = %d, tmp->length = %d\n", last_length, tmp->length);
		if (last_length == tmp->length)
		{
			while (x < tmp->length - 1 && last[x] == tmp->path[x])
			{
				// printf("last[%d] = %d, path[%d] = %d\n", x, last[x], x, tmp->path[x]);
				x++;
			}
			// printf("last[%d] = %d, path[%d] = %d\n", x, last[1], x, tmp->path[1]);
			if (x == last_length - 1)
			{
				// printf("RETURN 1 -> meme chemin : x = %d, last_lenght = %d", x, last_length);
				return (1);
			}
		}
		//copie le chemin du maillon dans last
		while (i < tmp->length - 1)
		{
			last[i] = tmp->path[i];
			// printf(" je copie last: last[%d] = %d\n", i, last[i]);
			i++;
		}
		last_length = tmp->length;
		//on passe au suivant
		tmp = tmp->next;
	}
	return (0);
}

/*
** backtrack_paths() cherche la premiere salle triple réservée, et rend la
** disponible. Retourne le numéro de cette salle pour savoir quel chemin
** supprimer plus tard.
*/

int		backtrack_paths(t_farm *farm)
{
	t_rooms		*tmp_rooms;

	tmp_rooms = farm->rooms;
	// ft_putstr("on bactrack\n");
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
	return (SUCCESS);
}

/*
** delete_first_path() si un chemin a été trouvé en rendant disponible la salle
** triple, alors il faut supprimer les chemins précédents qui l'utilisaient
*/

int		delete_first_path(t_farm *farm, int id_room)
{
	t_paths		*tmp;
	int			i;
	t_paths		*tmp_free;

	i = 0;
	tmp = farm->paths;
	while (tmp)
	{
		while (i < tmp->length - 1)
		{
			printf("tmp->path[i] = %d\n", tmp->path[i]);
			if (tmp->path[i] == id_room)
			{
				//nope faut free mais changer les pointeurs aussi, à voir plus tard
				printf("rentré tmp->path[i] = %d\n", tmp->path[i]);
				tmp_free = tmp;
				tmp = tmp->next;
				ft_memdel((void**)&tmp_free);
				return (SUCCESS);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
