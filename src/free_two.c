/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christel <christel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:56:08 by christel          #+#    #+#             */
/*   Updated: 2019/10/04 12:22:45 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** free_paths() frees found_paths structure.
*/

void	free_found_paths(t_farm *farm)
{
	t_paths	*tmp;
	t_paths	*new;

	tmp = farm->found_paths;
	while (tmp)
	{
		new = tmp->next;
		ft_memdel((void**)&tmp->path);
		ft_memdel((void**)&tmp);
		tmp = new;
	}
}

/*
** free_sets() frees each cell of the sets array from their paths structure.
*/

void	free_sets(t_farm *farm)
{
	int		i;
	t_paths	*tmp_tab;
	t_paths	*new;

	i = 0;
	while (i < farm->nb_sets)
	{
		tmp_tab = farm->sets[i];
		while (tmp_tab)
		{
			new = tmp_tab->next;
			ft_memdel((void**)&tmp_tab->path);
			ft_memdel((void**)&tmp_tab);
			tmp_tab = new;
		}
		i++;
	}
	ft_memdel((void**)&farm->sets);
}
