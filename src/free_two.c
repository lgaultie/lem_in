/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christel <christel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:56:08 by christel          #+#    #+#             */
/*   Updated: 2019/10/25 15:13:10 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** free_found_paths() frees found_paths structure.
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
** free_sets() frees sets structure.
*/

void	free_sets(t_farm *farm)
{
	t_sets	*tmp_set;
	t_sets	*new_set;
	t_paths	*tmp_path;
	t_paths	*new_path;

	tmp_set = farm->sets;
	while (tmp_set)
	{
		new_set = tmp_set->next;
		tmp_path = tmp_set->paths;
		while (tmp_path)
		{
			new_path = tmp_path->next;
			ft_memdel((void**)&tmp_path->path);
			ft_memdel((void**)&tmp_path);
			tmp_path = new_path;
		}
		ft_memdel((void**)&tmp_set);
		tmp_set = new_set;
	}
}

/*
** free_paths() frees paths structure.
*/

void	free_paths(t_farm *farm)
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
** free_farm_error() frees farm and writes an error message.
*/

int		free_farm_error(t_farm *farm)
{
	free_farm(farm);
	ft_putendl(ERROR_MSG);
	return (ERROR);
}

/*
** free_tab_error() frees tab.
*/

int		free_tab_error(char **tab)
{
	ft_free_tab(&tab);
	return (ERROR);
}
