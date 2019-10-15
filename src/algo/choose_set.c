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
** calc_moves() calculates how many moves we'll need on the set.
** Formula: nb_moves = (nb_ants + sum(length) - 2 * size_set) / size_set.
*/

int		calc_moves(int nb_moves, int size, int len, t_farm *farm)
{
    nb_moves = (farm->ants + len - 2 * size) / size;
	if (farm->visu == 1)
		print_nb_moves(size, nb_moves);
	return (nb_moves);
}

/*
** calc_length() calculates the total length of all the paths of a set.
*/

int		calc_length(t_paths *tmp, int length)
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
** minimum number of moves).
*/

void	choose_set(t_farm *farm)
{
	int		min_moves;
	t_sets	*tmp_set;

	min_moves = 0;
	tmp_set = farm->sets;
	if (farm->visu == 1)
		print_tab_paths(farm);
	while (tmp_set && tmp_set->paths)
	{
		if (min_moves == 0 || tmp_set->moves < min_moves)
			min_moves = tmp_set->moves;
		tmp_set = tmp_set->next;
	}
	farm->nb_moves = min_moves;
}
