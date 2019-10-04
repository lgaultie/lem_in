/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 10:18:36 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 11:37:39 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	print_tab_paths(t_farm *farm)
{
	int		i;
	int		x;
	t_paths	*tmp_tab;

	i = 0;
	ft_putstr("\n\e[36mALL POSSIBLE PATHS\e[0m\n");
	while (i < farm->nb_paths)
	{
		ft_putstr("\e[0m--------------------------------------------------------\n");
		ft_putstr("\e[33m");
		tmp_tab = farm->sets[i];
		while (tmp_tab)
		{
			x = 0;
			while(x < tmp_tab->length)
			{
				ft_putnbr(tmp_tab->path[x]);
				ft_putchar(' ');
				x++;
			}
			ft_putchar('\n');
			tmp_tab = tmp_tab->next;
		}
		i++;
	}
	ft_putstr("\e[0m--------------------------------------------------------\e[0m\n");
}

void	print_chosen_paths(t_farm *farm, int index)
{
	int		i;
	int		x;
	t_paths	*tmp_tab;

	i = 0;
	ft_putstr("Here the set of \e[36m");
	ft_putnbr(index + 1);
	ft_putstr(" path(s)\e[0m is the more optimized with\napproximately \e[36m");
	ft_putnbr(farm->nb_moves);
	ft_putstr("\e[0m moves to complete.\nSo we use: \e[32m\n");
	tmp_tab = farm->sets[index];
	while (tmp_tab)
	{
		x = 0;
		while(x < tmp_tab->length)
		{
			ft_putnbr(tmp_tab->path[x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		tmp_tab = tmp_tab->next;
	}
	ft_putstr("\e[0m");
	ft_putstr("--------------------------------------------------------\n\n");
}

void	print_free_rooms(t_farm *farm)
{
	t_rooms *tmp;

	tmp = farm->rooms;
	ft_putstr("--------------\n");
	while (tmp)
	{
		if (tmp->reserved == 1)
		{
			ft_putstr("salle ");
			ft_putnbr(tmp->room_id);
			ft_putstr(" reserved");
			ft_putchar(' ');
		}
		if (tmp->reserved == 0)
		{
			ft_putstr("salle ");
			ft_putnbr(tmp->room_id);
			ft_putstr(" libre");
			ft_putchar(' ');
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
	ft_putstr("--------------\n");
}

void	print_paths(t_farm *farm)
{
	t_paths		*tmp_path;
	tmp_path = farm->paths;
	ft_putchar('\n');
	while (tmp_path)
	{
		ft_putstr("PATHS actuels : ");
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
}

void	display_sets(t_farm *farm)
{
	int		i;
	int 	j;
	t_paths	**sets;
	t_paths *list;

	printf("****DISPLAY SETS****\n");
	sets = farm->sets;
	printf("sets addr: %p\n", sets);
	i = 0;
	while (i < farm->nb_paths)
	{
		printf("path[%d] addr: %p\n", i, sets[i]);
		list = sets[i];
		while (list)
		{
			j = 0;
			while (j < list->length)
			{
				printf("%d ", list->path[j]);
				j++;
			}
			printf("\n");
			list = list->next;
		}
		i++;
	}
}
