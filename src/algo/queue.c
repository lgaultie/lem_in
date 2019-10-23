/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:21:55 by cmouele           #+#    #+#             */
/*   Updated: 2019/10/23 17:06:05 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** unqueue() removes room id from the queue.
*/

int	unqueue(t_farm *farm)
{
	t_queue	*tmp_queue;

	tmp_queue = farm->queue;
	farm->queue = farm->queue->next;
	ft_memdel((void**)&tmp_queue);
	return (SUCCESS);
}

int	block_unqueue(t_farm *farm)
{
	t_queue	*tmp_queue;

	tmp_queue = farm->blocking_q;
	farm->blocking_q = farm->blocking_q->next;
	ft_memdel((void**)&tmp_queue);
	return (SUCCESS);
}

/*
** queue() adds room id to the queue.
*/

int	queue(t_farm *farm, int room_id)
{
	t_queue	*tmp;
	t_queue	*new;

	tmp = farm->queue;
	if (!(new = ft_memalloc(sizeof(t_queue))))
		return (ERROR);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		farm->queue = new;
	new->id = room_id;
	new->next = NULL;
	return (SUCCESS);
}

int	block_queue(t_farm *farm, int room_id)
{
	t_queue	*tmp;
	t_queue	*new;

	tmp = farm->blocking_q;
	if (!(new = ft_memalloc(sizeof(t_queue))))
		return (ERROR);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		farm->blocking_q = new;
	new->id = room_id;
	new->next = NULL;
	return (SUCCESS);
}
