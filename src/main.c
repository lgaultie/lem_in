/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:53:07 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/22 15:11:39 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** free_farm() frees farm.
*/

static void	free_farm(t_farm *farm, int **matrice)
{
	free_matrice(farm, matrice);
	free_rooms(farm->rooms);
	free_queue(farm);
	free_paths(farm);
	free_found_paths(farm);
	ft_memdel((void**)&farm->released_rooms);
	ft_memdel((void**)&farm->all_rooms);
	free_sets(farm);
	ft_memdel((void**)&farm);
}

/*
** max_paths() calculates the maximum number of paths we can find. It's
** the maximum number between the number of links to the start room, or the end
** room. The real number may be less.
*/

static int	max_paths(t_farm *farm)
{
	int		max_paths;
	int		links_of_start;
	int		links_of_end;
	t_rooms	*tmp_room;

	tmp_room = farm->rooms;
	links_of_start = farm->start->nb_links;
	links_of_end = farm->end->nb_links;
	if (links_of_end < links_of_start)
		max_paths = links_of_end;
	else
		max_paths = links_of_start;
	return (max_paths);
}

/*
** init_all_rooms() initializes an array of rooms. Each cell points to a
** room's structure link.
*/

static int	init_all_rooms(t_farm *farm)
{
	t_rooms	*tmp;
	int		i;

	tmp = farm->rooms;
	i = 0;
	if (!(farm->all_rooms = ft_memalloc(sizeof(t_rooms *) * farm->total_rooms)))
		return (ERROR);
	while (tmp)
	{
		farm->all_rooms[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	return (SUCCESS);
}

/*
** init_sets() initializes the sets structure. Each node contains the size of
** the set (how many paths there are in the set), the paths, and the number of
** moves needed for the ants to go from start to end.
*/

int			init_sets(t_farm *farm)
{
	t_sets	*tmp;
	t_sets	*new;
	int		i;

	i = 0;
	while (i < max_paths(farm))
	{
		tmp = farm->sets;
		if (!(new = ft_memalloc(sizeof(t_sets))))
			return (ERROR);
		if (tmp)
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			farm->sets = new;
		new->size = i + 1;
		new->next = NULL;
		i++;
	}
	return (SUCCESS);
}

/*
** main()
*/

int			main(int ac, char **av)
{
	int		error;
	t_farm	*farm;
	int		**matrice;

	error = 0;
	if (!(farm = ft_memalloc(sizeof(t_farm))))
		return (ERROR);
	if (ac > 2)
		return (free_farm_error(farm));
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "-v") != 0)
			return (free_farm_error(farm));
		farm->visu = 1;
	}
	if (read_input(farm, 1, error, error) == ERROR \
	|| init_all_rooms(farm) == ERROR \
	|| init_sets(farm) == ERROR \
	|| (matrice = matrice_create(farm, error)) == NULL
	|| allocate_sets(farm) == ERROR)
		return (free_farm_error(farm));
	free_farm(farm, matrice);
	return (FAILURE);
}
