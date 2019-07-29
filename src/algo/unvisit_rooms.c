/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unvisit_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 13:18:33 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/28 14:06:26 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		set_room_to_unvisited(t_farm *farm)
{
	// t_paths		*tmp;
	//
	// tmp = farm->paths;
	// free_queue(farm);
	// while (tmp->next)
	// {
	// 	tmp = tmp->next;
	// }
	// while (tmp)
	// {
	// 	// printf("room %d\n", )
	// 	tmp->visited = 0;
	// 	// printf("room n%d\n", tmp->room_id);
	// 	if (tmp->visited == 1 && tmp->nb_links > 2)
	// 	{
	// 		tmp->visited = 0;
	// 		// printf("room n%d\n", tmp->room_id);
	// 		return (SUCCESS);
	// 	}
	// 	tmp = tmp->prev;
	// }
	(void)farm;
	ft_putstr("faut dereserver les salles\n");
	return (SUCCESS);
}
