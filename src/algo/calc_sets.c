/* ************************************************************************** */
/*                                                                            */
/*   calc_sets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:03:01 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 16:03:37 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** calc_ants_to_send() calculates the number of ants to attribute to each path
** of a set. If the number of ants to send is negative, we delete the path from
** the set.
*/

int	calc_ants_to_send(t_sets *tmp_set, t_paths *tmp_path)
{
	int		deleted;
	t_paths	*next;

	deleted = 0;
	while (tmp_path)
	{
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
	return (deleted);
}

/*
** calc_moves() calculates how many moves we'll need on the set.
** Formula: nb_moves = (nb_ants + sum(length) - 2 * size_set) / size_set.
*/

int	calc_moves(int nb_moves, int size, int len, t_farm *farm)
{
    nb_moves = (farm->ants + len - 2 * size) / size;
	return (nb_moves);
}

/*
** calc_length() calculates the total length of all the paths of a set.
*/

int	calc_length(t_paths *tmp, int length)
{
	length = 0;
	while (tmp)
	{
		length += tmp->length;
		tmp = tmp->next;
	}
	return (length);
}
