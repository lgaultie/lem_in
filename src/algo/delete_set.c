/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 23:09:42 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/22 23:12:55 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** delete_set() frees and deletes the set of path we want to replace.
*/

void	delete_set(t_paths **first_path)
{
	t_paths	*tmp;
	t_paths	*new;
	int		i;

	i = 0;
	tmp = *first_path;
	while (tmp)
	{
		new = tmp->next;
		if (tmp->length > 0)
		{
			while (i < tmp->length)
			{
				ft_memdel((void**)&tmp->path);
				i++;
			}
			i = 0;
		}
		ft_memdel((void**)&tmp);
		tmp = new;
	}
}

void	replace_or_delete(int i, int j, t_farm *farm, t_paths *p_cpy)
{
	if (i > j)
	{
		delete_set(&(farm->last_set->paths));
		farm->last_set->paths = p_cpy;
	}
	else
		delete_set(&p_cpy);
}
