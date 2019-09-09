/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:53:07 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/09 14:29:30 by lgaultie         ###   ########.fr       */
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
	free_sets(farm);
	ft_memdel((void**)&farm);
}

/*
** max_paths() calculates the maximum number of paths we can find. It's
** the maximum number between the number of links to the start room, or the end
** room. The real number may be less.
*/

int		max_paths(t_farm *farm)
{
	int		max_paths;
	int		links_of_start;
	int		links_of_end;
	t_rooms	*tmp_room;

	tmp_room = farm->rooms;
	while (tmp_room)
	{
		if (tmp_room->start_end == 1)
			links_of_start = tmp_room->nb_links;
		if (tmp_room->start_end == 2)
			links_of_end = tmp_room->nb_links;
		tmp_room = tmp_room->next;
	}
	if (links_of_end < links_of_start)
		max_paths = links_of_end;
	else
		max_paths = links_of_start;
	ft_putstr("maximum possible de paths: ");
	ft_putnbr(max_paths);
	ft_putchar('\n');
	return (max_paths);
}

/*
** init_all_rooms()
*/

int		init_all_rooms(t_farm *farm)
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
** init_sets() initializes the array of paths structures.
*/

int		init_sets(t_farm *farm)
{
	int		max_path;

	max_path = max_paths(farm);
	if (!(farm->sets = ft_memalloc(sizeof(t_paths*) * max_path)))
		return (ERROR);
	return (SUCCESS);
}

/*
** main() creates farm structure, calls read_input() to read the map, creates
** the matrice, then frees the farm.
*/

int			main(void)
{
	int			line_nb;
	int			error;
	t_farm		*farm;
	int 		**matrice;

	line_nb = 1;
	error = 0;
	if (!(farm = ft_memalloc(sizeof(t_farm))) \
		|| read_input(farm, line_nb, error, error) == ERROR \
		|| init_all_rooms(farm) == ERROR \
		|| init_sets(farm) == ERROR \
		|| (matrice = matrice_create(farm)) == NULL)
		return (free_farm_error(farm));
	// choose_set(farm);
	how_much_ants_per_paths(farm);
	free_farm(farm, matrice);
	return (FAILURE);
}
