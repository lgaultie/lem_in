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
	int		ants_sent;
	t_paths	*tmp;
	int		i;

	i = 0;
	ants_sent = 0;
	index_of_set = choose_set(farm, ants_sent, ants_sent, ants_sent);
	if (farm->visu == 1)
		print_chosen_paths(farm, index_of_set);
	tmp = farm->sets[index_of_set];
	while (tmp)
	{
		i++;
		tmp->ants_to_send = farm->nb_moves - (tmp->length - 2);
		if (tmp->ants_to_send <= 0)
			delete_path(&(farm->sets[index_of_set]), tmp);
		else
			ants_sent += tmp->ants_to_send;
		if (farm->visu == 1)
		{
			ft_putstr("We'll send \e[35m");
			ft_putnbr(tmp->ants_to_send);
			ft_putstr(" ant(s)\e[0m in the path ");
			ft_putnbr(i);
			ft_putstr(".\n");
		}
		tmp = tmp->next;
	}
	tmp = farm->sets[index_of_set];
	while (ants_sent < farm->ants)
	{
		while (ants_sent < farm->ants && tmp)
		{
			tmp->ants_to_send++;
			ants_sent++;
			tmp = tmp->next;
		}
		tmp = farm->sets[index_of_set];
	}
	segment_ants(farm, index_of_set);
	if (send_ants(farm, index_of_set) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
