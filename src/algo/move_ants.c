/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:02:29 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/04 16:59:12 by lgaultie         ###   ########.fr       */
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
	int		length;
	int		i;
	int		deleted;

	tmp_set = farm->sets;
	deleted = 0;
	while (tmp_set)
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
				if (tmp_path->next)
				{
					tmp_path = tmp_path->next;
					delete_path(farm, &(tmp_set->paths), tmp_path->prev, i);
				}
				else
				{
					delete_path(farm, &(tmp_set->paths), tmp_path, i);
					tmp_path = NULL;
				}
				deleted = 1;
			}
			else
				tmp_set->ants_sent += tmp_path->ants_to_send;
			if (farm->visu == 1)
			{
				ft_putstr("We'll send \e[35m");
				ft_putnbr(tmp_path->ants_to_send);
				ft_putstr(" ant(s)\e[0m in the path ");
				ft_putnbr(i);
				ft_putstr(".\n");
			}
			tmp_path = tmp_path->next;
		}
		if (deleted == 1)
			return (allocate_sets(farm));
		tmp_set = tmp_set->next;
	}
	choose_set(farm);
	tmp_set = farm->sets;
	while (tmp_set)
	{
		if (tmp_set->moves == farm->nb_moves)
		{
			if (farm->visu == 1)
				print_chosen_paths(farm, tmp_set);
			while (tmp_set->ants_sent < farm->ants)
			{
				tmp_path = tmp_set->paths;
				while (tmp_set->ants_sent < farm->ants && tmp_path)
				{
					tmp_path->ants_to_send++;
					tmp_set->ants_sent++;
					tmp_path = tmp_path->next;
				}
			}
			segment_ants(tmp_set->paths);
			if (send_ants(farm, tmp_set->paths ) == ERROR)
				return (ERROR);
			break ;
		}
		tmp_set = tmp_set->next;
	}
	return (SUCCESS);
}
