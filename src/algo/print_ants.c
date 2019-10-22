/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christel <christel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:52:43 by christel          #+#    #+#             */
/*   Updated: 2019/10/22 15:12:15 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** print_ants() writes the paths taken by the ants on the standard output.
** f stands for farm, p for position, t for tmp
*/

static void	print_ants(t_farm *f, t_paths *t, int id_ant, int p)
{
	if (f->visu == 1)
	{
		if (f->all_rooms[t->path[p]]->name == f->all_rooms[t->path[t->length - 2]]->name)
			ft_putstr("\e[35m");
		else
			ft_putstr("\e[0m");
		if (f->all_rooms[t->path[p]]->start_end == 2)
			ft_putstr("\e[32m");
	}
	ft_putchar('L');
	ft_putnbr(id_ant + 1);
	ft_putchar('-');
	ft_putstr(f->all_rooms[t->path[p]]->name);
	if (f->visu == 1 && ((f->all_rooms[t->path[p]]->start_end == 1) \
		|| (f->all_rooms[t->path[p]]->start_end == 2)))
		ft_putstr("\e[0m");
	ft_putchar(' ');
}

/*
** print_turns() increments an id for each path of the optimized set that lets
** us know how many ants we can move, and we increment their position. If the
** position equals the length of the path, the ants has arrived to the end room
** and we don't need to increment the id anymore.
*/

static int	print_turns(t_farm *farm, t_paths *paths, int arrived, int *ants)
{
	t_paths	*tmp;
	int		i;

	tmp = paths;
	while (tmp)
	{
		i = tmp->left_seg;
		while (i <= tmp->right_seg)
		{
			ants[i]++;
			print_ants(farm, tmp, i, tmp->length - 1 - ants[i]);
			if (ants[i] == tmp->length - 1)
			{
				tmp->left_seg++;
				arrived++;
			}
			if (ants[i] == 1)
				break ;
			i++;
		}
		tmp = tmp->next;
	}
	return (arrived);
}

/*
** send_ants() creates an array of ants to track their position in the path.
** While all ants aren't arrived to the end room, it calls print_turns().
*/

int			send_ants(t_farm *farm, t_paths *paths)
{
	int		*ants;
	int		nb_lines;
	int		arrived;

	if (!(ants = ft_memalloc(sizeof(int) * farm->ants)))
		return (ERROR);
	nb_lines = 0;
	arrived = 0;
	if (farm->visu == 1)
	{
		ft_putstr("\n· \e[35mpurple\e[0m: first step of a new ant.\n· ");
		ft_putstr("white: ant ongoing.\n· \e[32mgreen\e[0m: ant arrives.\n\n");
	}
	while (arrived < farm->ants)
	{
		arrived = print_turns(farm, paths, arrived, ants);
		ft_putchar('\n');
		nb_lines++;
	}
	ft_memdel((void**)&ants);
	return (SUCCESS);
}
