/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 10:18:36 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 15:19:49 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	print_tab_paths(t_farm *farm)
{
	int		i;
	int		x;
	t_paths	*tmp_tab;

	i = 0;
	ft_putstr("\n\e[35mAll possible paths:\n\e[0m");
	while (i < farm->nb_paths)
	{
		ft_putstr("\e[0m--------------------------------------------------\e[33m\n");
		tmp_tab = farm->sets[i];
		while (tmp_tab)
		{
			x = tmp_tab->length - 1;
			while(x > -1)
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
	ft_putstr("\e[0m--------------------------------------------------\n\n");
}

void	print_chosen_paths(t_farm *farm, int index)
{
	int		i;
	int		x;
	t_paths	*tmp_tab;

	i = 0;
	ft_putstr("\nAs we have \e[36m");
	ft_putnbr(farm->ants);
	ft_putstr(" ants\e[0m, the set of \e[36m");
	ft_putnbr(index + 1);
	ft_putstr(" path(s)\e[0m \nis the more optimized with approximately\n\e[36m");
	ft_putnbr(farm->nb_moves);
	ft_putstr(" moves\e[0m to complete.\nSo we use this set of path(s): \n");
	tmp_tab = farm->sets[index];
	ft_putstr("--------------------------------------------------\n\e[32m");
	while (tmp_tab)
	{
		x = tmp_tab->length - 1;
		while(x > -1)
		{
			//farm->all_rooms[tmp_tab->path[x]]->name
			ft_putstr(farm->all_rooms[tmp_tab->path[x]]->name);
			// ft_putnbr(tmp_tab->path[x]);
			ft_putchar(' ');
			x--;
		}
		ft_putchar('\n');
		tmp_tab = tmp_tab->next;
	}
	ft_putstr("\e[0m");
	ft_putstr("--------------------------------------------------\n\n");
	ft_putstr("\n· \e[35mpurple\e[0m: first step of a new ant.\n");
	ft_putstr("· blanck: ants ongoing.");
	ft_putstr("\n· \e[32mgreen\e[0m: ant arrives.\n\n");
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
