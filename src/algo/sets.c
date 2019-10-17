/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:02:29 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/16 15:27:58 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** segment_ants() creates, for each path, a segment with the id of the first
** ant and the id of the last ant.
*/

static void	segment_ants(t_paths *paths)
{
	t_paths	*tmp_path;
	int		id_ant;
	int		left_segment;
	int		right_segment;

	tmp_path = paths;
	id_ant = 0;
	while (tmp_path)
	{
		left_segment = id_ant;
		right_segment = left_segment + tmp_path->ants_to_send - 1;
		id_ant = right_segment + 1;
		tmp_path->left_seg = left_segment;
		tmp_path->right_seg = right_segment;
		tmp_path = tmp_path->next;
	}
}

/*
** remaining_ants() checks if the number of ants sent is lower than the
** original number. If true, it dispatches one ant in each path until the
** original number is reached.
*/

static void	remaining_ants(t_farm *farm, t_sets *set)
{
	t_paths	*tmp_path;

	tmp_path = set->paths;
	while (tmp_path && set->ants_sent < farm->ants)
	{
		tmp_path->ants_to_send++;
		set->ants_sent++;
		tmp_path = tmp_path->next;
	}
}

/*
** choose_set() searches for the best set of paths to use (the one with the
** minimum number of moves), then calls remaining_ants(), segment_ants() and
** send_ants().
*/

static int	choose_set(t_farm *farm)
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
	tmp_set = farm->sets;
	while (tmp_set && tmp_set->paths && tmp_set->moves != farm->nb_moves)
		tmp_set = tmp_set->next;
	if (farm->visu == 1)
		print_chosen_paths(farm, tmp_set);
	remaining_ants(farm, tmp_set);
	segment_ants(tmp_set->paths);
	if (send_ants(farm, tmp_set->paths) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/*
** allocate_sets() calculates the number moves we need for each set and the
** number of ants we need to send to each path. Then it calls choose_set() to
** find the optimized set.
*/

int			allocate_sets(t_farm *farm)
{
	t_sets	*tmp_set;
	t_paths	*tmp_path;
	int		length;
	int		deleted;

	tmp_set = farm->sets;
	while (tmp_set && tmp_set->paths)
	{
		tmp_path = tmp_set->paths;
		length = calc_length(tmp_set->paths, 0);
		tmp_set->moves = calc_moves(0, tmp_set->size, length, farm);
		if ((deleted = calc_ants_to_send(tmp_set, tmp_path)) == 1)
		{
			tmp_set->ants_sent = 0;
			deleted = 0;
			tmp_path = tmp_set->paths;
			continue ;
		}
		tmp_set = tmp_set->next;
	}
	if (farm->visu == 1)
		print_nb_moves(tmp_set);
	if (choose_set(farm) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
