/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:35:46 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 15:42:55 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** free_paths() frees paths structure.
*/

void		free_paths(t_farm *farm)
{
	t_paths	*tmp;
	t_paths	*new;

	tmp = farm->paths;
	while (tmp)
	{
		new = tmp->next;
		ft_memdel((void**)&tmp->path);
		ft_memdel((void**)&tmp);
		tmp = new;
	}
}

/*
** free_queue() frees queue structure.
*/

void		free_queue(t_farm *farm)
{
	t_queue	*tmp;
	t_queue	*new;

	tmp = farm->queue;
	while (tmp)
	{
		new = tmp->next;
		ft_memdel((void**)&tmp);
		tmp = new;
	}
	farm->queue = NULL;
}

/*
** free_links() frees links structure.
*/

static void	free_links(t_links *links)
{
	t_links	*tmp;

	while (links->next)
	{
		tmp = links;
		links = links->next;
		ft_memdel((void**)&tmp->name);
		ft_memdel((void**)&tmp);
	}
	if (!(links->next))
	{
		ft_memdel((void**)&links->name);
		ft_memdel((void**)&links);
	}
}

/*
** free_rooms() frees rooms structure.
*/

void		free_rooms(t_rooms *rooms)
{
	t_rooms	*tmp;

	while (rooms)
	{
		if (rooms->links)
			free_links(rooms->links);
		tmp = rooms;
		rooms = rooms->next;
		ft_memdel((void**)&tmp->name);
		ft_memdel((void**)&tmp);
	}
}

/*
** free_matrice() frees the matrice.
*/

void		free_matrice(t_farm *farm)
{
	int	i;

	i = 0;
	while (i < farm->total_rooms)
	{
		if (farm->matrice[i] == NULL)
			return ;
		ft_memdel((void**)&(farm->matrice[i]));
		i++;
	}
	ft_memdel((void**)&(farm->matrice));
}
