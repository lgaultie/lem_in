/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 10:18:36 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 17:00:09 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	print_nb_moves(int i, int nb_moves)
{
	ft_putstr("Using \e[36m");
	ft_putnbr(i + 1);
	ft_putstr(" \e[0mpath(s) will take \e[36m");
	ft_putnbr(nb_moves);
	ft_putstr(" \e[0mmoves.\n");
}

void	print_tab_paths(t_farm *farm)
{
	int		i;
	int		x;
	t_paths	*tmp_tab;

	i = 0;
	ft_putstr("\e[35mAll possible paths:\n\e[0m");
	while (i < farm->nb_paths)
	{
		ft_putstr("\e[0m---------------------------------------------\e[33m\n");
		tmp_tab = farm->sets[i];
		while (tmp_tab)
		{
			x = tmp_tab->length - 1;
			while (x > -1)
			{
				ft_putstr(farm->all_rooms[tmp_tab->path[x]]->name);
				ft_putchar(' ');
				x--;
			}
			ft_putchar('\n');
			tmp_tab = tmp_tab->next;
		}
		i++;
	}
	ft_putstr("\e[0m---------------------------------------------\n\n");
}

void	print_chosen_paths_bis(t_farm *farm, int index)
{
	ft_putstr("\nAs we have \e[36m");
	ft_putnbr(farm->ants);
	ft_putstr(" ants\e[0m, the set of \e[36m");
	ft_putnbr(index + 1);
	ft_putstr(" path(s)\e[0m \n");
	ft_putstr("is the more optimized with approximately\n\e[36m");
	ft_putnbr(farm->nb_moves);
	ft_putstr(" moves\e[0m to complete.\nSo we use this set of path(s): \n");
}

void	print_chosen_paths(t_farm *farm, int index)
{
	int		i;
	int		x;
	t_paths	*tmp_tab;

	i = 0;
	print_chosen_paths_bis(farm, index);
	tmp_tab = farm->sets[index];
	ft_putstr("---------------------------------------------\n\e[32m");
	while (tmp_tab)
	{
		x = tmp_tab->length - 1;
		while (x > -1)
		{
			ft_putstr(farm->all_rooms[tmp_tab->path[x]]->name);
			ft_putchar(' ');
			x--;
		}
		ft_putchar('\n');
		tmp_tab = tmp_tab->next;
	}
	ft_putstr("\e[0m---------------------------------------------\n");
}
