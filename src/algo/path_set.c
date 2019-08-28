/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 23:35:40 by cmouele           #+#    #+#             */
/*   Updated: 2019/08/27 23:35:41 by cmouele          ###   ########.fr       */
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

	ft_putstr("in save_path()\n");
	paths_cpy = NULL;
	if (init_paths_cpy(paths, &paths_cpy) == ERROR)
		return (ERROR);
	paths_on_set = farm->all_paths[farm->nb_paths];
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
	if (farm->all_paths[farm->nb_paths] == NULL)
	{
		farm->all_paths[farm->nb_paths] = paths_cpy;
		print_tab_paths(farm); // TMP
	}
	/*else
	{
		while (paths_on_set)
		{
			ft_putstr("length of path on set: ");
			ft_putnbr(paths_on_set->length);
			ft_putchar('\n');
			i += paths_on_set->length;
			paths_on_set = paths_on_set->next;
		}
		while (paths_cpy)
		{
			ft_putstr("length of path on set cpy: ");
			ft_putnbr(paths_cpy->length);
			ft_putchar('\n');
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
		// END TMP
		// on garde le set qui a le nombre le plus petit
		// si on garde les anciens chemins, on ne change rien
		// sinon, on free les anciens chemins, on duplique les nouveaux pour les mettre a la place des anciens
		if (i <= j)
		{
			ft_putstr("i & j =  ");
			ft_putnbr(i);
			ft_putchar(' ');
			ft_putnbr(j);
			ft_putchar('\n');
		}
		else
		{
			ft_putstr("i & j =  ");
			ft_putnbr(i);
			ft_putchar(' ');
			ft_putnbr(j);
			ft_putchar('\n');
		}
	}*/
	return (SUCCESS);
}