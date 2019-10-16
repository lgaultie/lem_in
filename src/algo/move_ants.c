/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
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
** allocate_sets() calculates the number moves we need for each set and the
** number of ants we need to send to each path. If the number of ants to send
** is negative, we delete the path from the set and call the function again to
** calculate the number of moves and ants. Then it calls choose_set() to find
** the optimized set. If the number of ants sent is lower than the original
** number, we dispatch one ant in each path until the original number is
** reached. Then it calls segment_ants() and send_ants().
*/

int			allocate_sets(t_farm *farm)
{
	t_sets	*tmp_set;
	t_paths	*tmp_path;
	t_paths *next;
	int		length;
	int		i;
	int		deleted;

	tmp_set = farm->sets;
	deleted = 0;
	while (tmp_set && tmp_set->paths)
	{
		i = 0;
		tmp_path = tmp_set->paths;
		length = calc_length(tmp_set->paths, 0);
		tmp_set->moves = calc_moves(0, tmp_set->size, length, farm);
		while (tmp_path)
		{
			i++;
			tmp_path->ants_to_send = tmp_set->moves - (tmp_path->length - 2);
			if (tmp_path->ants_to_send <= 0 && tmp_set->size > 1)
			{
				next = tmp_path->next;
				delete_path(tmp_set, &(tmp_set->paths), tmp_path);
				tmp_path = next;
				deleted = 1;
				continue ;
			}
			if (deleted == 1)
			{
				tmp_path = tmp_path->next;
				continue;
			}
			tmp_set->ants_sent += tmp_path->ants_to_send;
			tmp_path = tmp_path->next;
		}
		if (deleted == 1)
		{
			tmp_set->ants_sent = 0;
			deleted = 0;
			tmp_path = tmp_set->paths;
			continue ;
		}
		tmp_set = tmp_set->next;
	}
	tmp_set = farm->sets;
	while (tmp_set && tmp_set->paths)
	{
		if (farm->visu == 1)
			print_nb_moves(tmp_set->size, tmp_set->moves);
		tmp_set = tmp_set->next;
	}
	choose_set(farm);
	tmp_set = farm->sets;
	while (tmp_set && tmp_set->paths && tmp_set->moves != farm->nb_moves)
		tmp_set = tmp_set->next;
	if (farm->visu == 1)
		print_chosen_paths(farm, tmp_set);
	tmp_path = tmp_set->paths;
	while (tmp_path && tmp_set->ants_sent < farm->ants)
	{
		tmp_path->ants_to_send++;
		tmp_set->ants_sent++;
		tmp_path = tmp_path->next;
	}
	segment_ants(tmp_set->paths);
	if (send_ants(farm, tmp_set->paths) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
