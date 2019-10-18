/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 10:18:36 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/17 16:30:13 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_nb_moves(int i, int nb_moves)
{
	ft_putstr("Using \e[36m");
	ft_putnbr(i);
	ft_putstr(" \e[0mpath(s) will take \e[36m");
	ft_putnbr(nb_moves);
	ft_putstr(" \e[0mmoves.\n");
}

void		print_tab_paths(t_farm *farm)
{
	int		i;
	t_sets	*tmp_set;
	t_paths	*tmp_path;

	ft_putstr("\e[35mAll possible paths:\n\e[0m");
	tmp_set = farm->sets;
	while (tmp_set)
	{
		ft_putstr("\e[0m---------------------------------------------\e[33m\n");
		tmp_path = tmp_set->paths;
		while (tmp_path)
		{
			i = tmp_path->length - 1;
			while (i > -1)
			{
				ft_putstr(farm->all_rooms[tmp_path->path[i]]->name);
				ft_putchar(' ');
				i--;
			}
			ft_putchar('\n');
			tmp_path = tmp_path->next;
		}
		tmp_set = tmp_set->next;
	}
	ft_putstr("\e[0m---------------------------------------------\n\n");
}

static void	print_chosen_paths_bis(t_farm *farm, int size)
{
	ft_putstr("\nAs we have \e[36m");
	ft_putnbr(farm->ants);
	ft_putstr(" ants\e[0m, the set of \e[36m");
	ft_putnbr(size);
	ft_putstr(" path(s)\e[0m \n");
	ft_putstr("is the more optimized with approximately\n\e[36m");
	ft_putnbr(farm->nb_moves);
	ft_putstr(" moves\e[0m to complete.\nSo we use this set of path(s): \n");
}

void		print_chosen_paths(t_farm *farm, t_sets *set)
{
	int		i;
	t_paths	*tmp_path;

	print_chosen_paths_bis(farm, set->size);
	tmp_path = set->paths;
	ft_putstr("---------------------------------------------\n\e[32m");
	while (tmp_path)
	{
		i = tmp_path->length - 1;
		while (i > -1)
		{
			ft_putstr(farm->all_rooms[tmp_path->path[i]]->name);
			ft_putchar(' ');
			i--;
		}
		ft_putchar('\n');
		tmp_path = tmp_path->next;
	}
	ft_putstr("\e[0m---------------------------------------------\n");
}
