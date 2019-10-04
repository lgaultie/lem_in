/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:02:29 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/04 11:06:16 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** segment_ants() creates, for each path, a segment with the id of the first
** ant and the id of the last ant.
*/

static void	segment_ants(t_farm *farm, int index_of_set)
{
	t_paths	*tmp;
	int		id_ant;
	int		left_segment;
	int		right_segment;

	tmp = farm->sets[index_of_set];
	id_ant = 0;
	while (tmp)
	{
		left_segment = id_ant;
		right_segment = left_segment + tmp->ants_to_send - 1;
		id_ant = right_segment + 1;
		tmp->left_seg = left_segment;
		tmp->right_seg = right_segment;
		tmp = tmp->next;
	}
}

int			calc_nb_moves(t_farm *farm, int nb_moves, int length, int i)
{
	if (farm->ants >= i + 1)
		nb_moves = (farm->ants + length - (2 * (i + 1))) / (i + 1);
	return (nb_moves);
}

/*
** choose_set() searches for the best set of paths to use (the one with the
** minimum number of moves). It returns the index of the optimized set.
** Formula: nb_moves = (nb_ants + sum(length) - (2 * nb_paths)) / nb_paths.
*/

static int	choose_set(t_farm *farm, int i, int length, int nb_moves)
{
	int		min;
	int		index_min;
	t_paths	*tmp;

	min = 0;
	index_min = 0;
	tmp = farm->sets[i];
	while (i < farm->nb_paths)
	{
		length = 0;
		while (tmp)
		{
			length += farm->sets[i]->length;
			tmp = tmp->next;
		}
		nb_moves = calc_nb_moves(farm, nb_moves, length, i);
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

/*
** ants_per_paths() calls choose_set() to find the optimized set of paths. It
** then calculates the number of ants we need to send to each path of the
** optimized set and saves it. Formula: nb_ants = nb_moves - (length - 2). If
** the number of ants to send is negative, we delete the path from the set. If
** the number of ants sent is different from the original number, we dispatch
** ants randomly in the paths until the original number is reached.
*/

int			ants_per_paths(t_farm *farm)
{
	int		index_of_set;
	int		total_sent;
	t_paths	*tmp;

	total_sent = 0;
	index_of_set = choose_set(farm, total_sent, total_sent, total_sent);
	if (farm->visu == 1)
	{
		print_tab_paths(farm);
		print_chosen_paths(farm, index_of_set);
	}
	tmp = farm->sets[index_of_set];
	while (tmp)
	{
		tmp->ants_to_send = farm->nb_moves - (tmp->length - 2);
		if (tmp->ants_to_send <= 0)
			delete_path(&(farm->sets[index_of_set]), tmp);
		else
			total_sent += tmp->ants_to_send;
		tmp = tmp->next;
	}
	tmp = farm->sets[index_of_set];
	while (total_sent < farm->ants)
	{
		while (total_sent < farm->ants && tmp)
		{
			tmp->ants_to_send++;
			total_sent++;
			tmp = tmp->next;
		}
		tmp = farm->sets[index_of_set];
	}
	segment_ants(farm, index_of_set);
	if (send_ants(farm, index_of_set) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
