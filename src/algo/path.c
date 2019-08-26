/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:15:36 by cmouele           #+#    #+#             */
/*   Updated: 2019/08/25 15:39:07 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	print_all_paths(t_farm *farm)
{
	// TMP
	t_paths		*tmp_path;
	tmp_path = farm->paths;
	ft_putchar('\n');
	while (tmp_path)
	{
		ft_putstr("PATHS actuels : ");
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
			ft_putstr("add room to path: ");
			ft_putnbr(tmp_rooms->room_id);
			ft_putchar('\n');
			// printf("add room %s in path\n", tmp_rooms->name);
			path->path[i] = tmp_rooms->room_id;
			i++;
			break ;
		}
		tmp_rooms = tmp_rooms->next;
	}
	print_all_paths(farm);
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
** save_path() saves in an array of paths the paths combinations, in an
** incremental order. If we have 2 sets that have the same number of paths, we
** compare them and keep the set that has the lower number of rooms.
*/

void	save_path(t_farm *farm, t_paths *paths)
{
	// dupliquer t_paths *paths
	t_paths	*paths_on_set;
	int i;

	ft_putstr("save path\n");
	paths_on_set = farm->all_paths[farm->nb_paths];
	i = 0;
	if (farm->all_paths[farm->nb_paths] == NULL)
		farm->all_paths[farm->nb_paths] = paths;
	else
	{
		/*
		// on compte le nombre total de salles dans le set déjà enregistré
		while (paths_on_set)
		{
			i += paths_on_set->length;
			paths_on_set = paths_on_set->next;
		}
		ft_putstr("number of total rooms in set ");
		ft_putnbr(farm->nb_paths);
		ft_putstr(" : ");
		ft_putnbr(i);
		ft_putchar('\n');
		// on compte le nombre total de salles dans le set que l'on vient de trouver
		// on garde le set qui a le nombre le plus petit
		// si on garde les anciens chemins, on ne change rien
		// sinon, on free les anciens chemins, on duplique les nouveaux pour les mettre a la place des anciens
		 */
	}
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
		{
			retrieve_path(farm, tmp_path, tmp_rooms->room_id, 0);
			if (check_paths(farm) == SUCCESS)
				return (FAILURE);
			farm->nb_paths++;
			save_path(farm, tmp_path);
		}
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
