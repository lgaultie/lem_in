/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:35:46 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/18 18:35:42 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		free_list(t_rooms *rooms)
{
	t_rooms		*tmp;
	// t_links		*tmp2;

	while (rooms)
	{
		tmp = rooms;
		rooms = rooms->next;
		// if (rooms->links)
		// {
		// 	while (rooms->links && rooms->links->next)
		// 	{
		// 		tmp2 = rooms->links;
		// 		rooms->links = rooms->links->next;
		// 		free(tmp2->name);
		// 		free(tmp2);
		// 	}
		// }
		free(tmp->name);
		free(tmp);
	}
}
