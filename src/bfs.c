/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 10:42:55 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/22 15:36:19 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		add_queue(t_farm *farm)
{
	t_queue		*new;
	t_queue		*tmp;

	tmp = farm->queue;
	if (!(new = ft_memalloc(sizeof(t_queue))))
		return (ERROR);
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		farm->queue = new;
	farm->queue->id = farm->rooms->room_id;
	return (SUCCESS);
}

int		bfs(t_farm *farm)
{
	t_farm	*tmp;
	int		nb_link;

	nb_link = 0;
	tmp = farm;
	while (farm->rooms)
	{
		if (farm->rooms->start_end == 1)
		{
			if (add_queue(farm) == ERROR)
				return (ERROR);
			printf("name = %s, id = %d, start-end = %d\n", farm->rooms->name, farm->rooms->room_id, farm->rooms->start_end);
			printf("queue->id = %d\n", farm->queue->id);
		}
		farm->rooms = farm->rooms->next;
	}
	return (SUCCESS);
}
