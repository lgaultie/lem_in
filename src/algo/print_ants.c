// Header 42

#include <lem_in.h>

/*
** print_ants() writes the paths taken by the ants on the standard output.
*/

static void	print_ants(t_farm *farm, t_paths *tmp, int id_ant, int pos)
{
	ft_putchar('L');
	ft_putnbr(id_ant + 1);
	ft_putchar('-');
	ft_putstr(farm->all_rooms[tmp->path[pos]]->name);
	ft_putchar(' ');
}

/*
** send_ants() creates an array of ants to track their position in the path.
** For each round, for each path of the optimized set, we increment an id that
** lets us know how many ants we can move, and we increment their position. If
** the position equals the length of the path, the ants has arrived to the end
** room ans we don't need to increment this ants anymore.
*/

int			send_ants(t_farm *farm, int index_of_set)
{
	int		*ants;
	int		i;
	t_paths	*tmp;
	int		arrived;
	int		nb_lines;

	nb_lines = 0;
	if (!(ants = ft_memalloc(sizeof(int) * farm->ants)))
		return (ERROR);
	arrived = 0;
	while (arrived < farm->ants)
	{
		tmp = farm->sets[index_of_set];
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
		ft_putchar('\n');
		nb_lines++;
	}
	ft_memdel((void**)&ants);
	return (SUCCESS);
}
