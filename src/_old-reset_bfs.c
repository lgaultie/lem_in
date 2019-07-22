/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 10:32:24 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/17 10:32:25 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int reset_bfs(t_farm *farm)
{
    t_rooms *tmp_rooms;

    tmp_rooms = farm->rooms;
    while (tmp_rooms != NULL)
    {
        tmp_rooms->visited = 0;
        tmp_rooms = tmp_rooms->next;
    }
    free_queue(farm);
    return (SUCCESS);
}