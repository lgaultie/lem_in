// Header 42

#include <lem_in.h>

/*
** print_ants()
*/
/*
static void	print_ants()
{

}
*/

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
	int		j;
	t_paths	*tmp;

	if (!(ants = ft_memalloc(sizeof(int) * farm->ants)))
		return (ERROR);
	i = 0;
	while (i < farm->nb_moves) // revoir nb_moves
	{
		tmp = farm->sets[index_of_set];
		while (tmp)
		{
			j = 0;
			while (j < (i + 1))
			{
				if (ants[tmp->left_seg + j] < tmp->length \
					&& (tmp->left_seg + j) <= tmp->right_seg)
				{
					printf("L%d-room ", tmp->left_seg + j + 1);
					ants[tmp->left_seg + j]++;
				}
				j++;
			}
			tmp = tmp->next;
		}
		i++;
		printf("\n");
	}
	// create a function to print rooms names associated with each ant (print_ants())
	// free int *ants
	return (SUCCESS);
}