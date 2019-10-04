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
** Formula: nb_moves = (nb_ants + sum(length) - (2 * nb_paths)) / nb_paths.
*/

static int	calc_nb_moves(int nb_moves, int i, int length, t_farm *farm)
{
	if (farm->ants >= i + 1)
		nb_moves = (farm->ants + length - (2 * (i + 1))) / (i + 1);
	if (farm->visu == 1)
		print_nb_moves(i, nb_moves);
	return (nb_moves);
}

/*
** calc_length
*/

static int	calc_length(t_paths *tmp, t_farm *farm, int length, int i)
{
	length = 0;
	while (tmp)
	{
		length += farm->sets[i]->length;
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
	tmp = farm->sets[i];
	if (farm->visu == 1)
		print_tab_paths(farm);
	while (i < farm->nb_paths)
	{
		length = calc_length(tmp, farm, length, i);
		nb_moves = calc_nb_moves(nb_moves, i, length, farm);
		if (min == 0 || nb_moves < min)
		{
			index_min = i;
			min = nb_moves;
		}
		i++;
		if (i < farm->nb_paths)
			tmp = farm->sets[i];
	}
	farm->nb_moves = min;
	return (index_min);
}
