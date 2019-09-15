/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 10:18:36 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/15 14:03:07 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_tab_paths(t_farm *farm)
{
	int	i;
	t_paths	*tmp_tab;

	i = 0;
	ft_putstr("-----------tableau de save_paths-------------\n");
	while (i < farm->nb_paths)
	{
		tmp_tab = farm->sets[i];
		ft_putstr("i = ");
		ft_putnbr(i);
		ft_putchar('\n');
		while (tmp_tab)
		{
			int x = 0;
			while(x < tmp_tab->length)
			{
				ft_putnbr(tmp_tab->path[x]);
				ft_putchar(' ');
				x++;
			}
			ft_putchar('\n');
			tmp_tab = tmp_tab->next;
		}
		ft_putstr("\n-----------tableau de save_paths-------------\n");
		i++;
	}
	ft_putchar('\n');
}

void		print_free_rooms(t_farm *farm)
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

void		print_paths(t_farm *farm)
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
