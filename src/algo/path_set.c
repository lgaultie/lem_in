/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 23:35:40 by cmouele           #+#    #+#             */
/*   Updated: 2019/08/28 15:59:13 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** init_paths_cpy() copies current paths into a new structure.
*/

static int	init_paths_cpy(t_paths *paths, t_paths **paths_cpy)
{
	t_paths	*new_path;
	t_paths	*prev_path;
	int		i;

	ft_putstr("in init_save_path()\n");
	new_path = NULL;
	while (paths)
	{
		prev_path = new_path;
		if ((new_path = ft_memalloc(sizeof(t_paths))) == NULL)
			return (ERROR);
		if (prev_path)
			prev_path->next = new_path;
		else
			*paths_cpy = new_path;
		new_path->length = paths->length;
		if (new_path->length > 0)
		{
			if ((new_path->path = ft_memalloc(sizeof(int) * new_path->length)) == NULL)
				return (ERROR);
			i = 0;
			while (i < new_path->length)
			{
				new_path->path[i] = paths->path[i];
				i++;
			}
		}
		new_path->prev = prev_path;
		new_path->next = NULL;
		paths = paths->next;
	}
	return (SUCCESS);
}

void	delete_paths_on_set(t_farm *farm)
{
	t_paths	*tmp;
	int		i;

	i = 0;
	while (paths_on_set)
	{
		tmp = paths_on_set->next;
		if (paths_on_set->length > 0)
		{
			while (i < paths_on_set->length)
			{
				ft_memdel((void**)&paths_on_set);
				i++;
			}
		}
		ft_memdel((void**)&paths_on_set);
		paths_on_set = tmp;
	}
	(void)farm;
	farm->all_paths[farm->nb_paths - 1] = NULL;
}

// void	cpy_new_set(t_farm *farm, t_paths *paths_cpy)
// {
//
// }

/*
** save_path() saves in an array of paths the paths combinations, in an
** incremental order. If we have 2 sets that have the same number of paths, we
** compare them and keep the set that has the lower number of rooms.
*/

int			save_path(t_farm *farm, t_paths *paths)
{
	t_paths	*paths_on_set;
	t_paths	*paths_cpy;
	int		i;
	int		j;

	if (farm->nb_paths <= 0)
		return (SUCCESS);
	ft_putstr("in save_path() avec farm->nb_paths = ");
	ft_putnbr(farm->nb_paths);
	ft_putchar('\n');
	paths_cpy = NULL;
	//copie les paths actuels dans path_cpy
	if (init_paths_cpy(paths, &paths_cpy) == ERROR)
		return (ERROR);
	//on prend le pointeur des paths actuels dans le tableau
	paths_on_set = farm->all_paths[farm->nb_paths - 1];
	// TMP
	t_paths	*tmp_path = paths_cpy;
	ft_putchar('\n');
	while (tmp_path)
	{
		ft_putstr("PATHS cpy : ");
		int x = 0;
		while(x < tmp_path->length)
		{
			ft_putnbr(tmp_path->path[x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		tmp_path = tmp_path->next;
	}
	ft_putchar('\n');
	// END TMP
	i = 0;
	j = 0;
	if (paths_on_set == NULL)
	{
		farm->all_paths[farm->nb_paths - 1] = paths_cpy;
		print_tab_paths(farm); // TMP
	}
	// else
	if (farm->nb_paths == 3)
	{
		paths_on_set = farm->all_paths[farm->nb_paths - 1];
		ft_putstr("OHH YA DEJA DES PATHS DANS LE TABBB\n");
		while (paths_on_set)
		{
			i += paths_on_set->length;
			paths_on_set = paths_on_set->next;
		}
		while (paths_cpy)
		{
			j += paths_cpy->length;
			paths_cpy = paths_cpy->next;
		}
		// TMP
		ft_putstr("number of total rooms in registered set ");
		ft_putnbr(farm->nb_paths);
		ft_putstr(" : ");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putstr("number of total rooms in new set : ");
		ft_putnbr(j);
		ft_putchar('\n');
		ft_putstr("length of path_on_set et paths_cpy -->  ");
		ft_putnbr(i);
		ft_putstr(" et ");
		ft_putnbr(j);
		ft_putchar('\n');
		// END TMP
		// sinon, on free les anciens chemins, on duplique les nouveaux pour les mettre a la place des anciens
		if (i < j)
			return (SUCCESS);
		else
		{
			ft_putstr("je remplace les chemins\n");
			delete_paths_on_set(farm);
			// cpy_new_set(farm, paths_cpy);
			print_tab_paths(farm); // TMP
		}
	}
	return (SUCCESS);
}
