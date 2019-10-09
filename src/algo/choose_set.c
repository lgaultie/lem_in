/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:03:01 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 16:03:37 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** calc_nb_moves() calculates how many moves we'll need on the set.
** Formula: nb_moves = (nb_ants + sum(length) - size_set) / size_set.
*/

static int	calc_nb_moves(int nb_moves, int i, int length, t_farm *farm)
{
    nb_moves = (farm->ants + length - 2 * farm->sets_size[i]) / farm->sets_size[i];
	if (farm->visu == 1)
		print_nb_moves(i, nb_moves);
	return (nb_moves);
}

/*
** calc_length() calculates the total length of all the paths of a set.
*/

static int	calc_length(t_paths *tmp, int length)
{
	length = 0;
	while (tmp)
	{
		length += tmp->length;
		tmp = tmp->next;
	}
	return (length);
}

/*
** choose_set() searches for the best set of paths to use (the one with the
** minimum number of moves). It returns the index of the optimized set.
*/

int			choose_set(t_farm *farm, int i, int length, int nb_moves)
{
	int		min;
	int		index_min;
	t_paths	*tmp;

	min = 0;
	index_min = 0;
	if (farm->visu == 1)
		print_tab_paths(farm);
	while (i < farm->nb_sets)
	{
        tmp = farm->sets[i];
		length = calc_length(tmp, length);
		nb_moves = calc_nb_moves(nb_moves, i, length, farm);
		if (min == 0 || nb_moves < min)
		{
			index_min = i;
			min = nb_moves;
		}
		i++;
	}
	farm->nb_moves = min;
	return (index_min);
}
