/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 11:03:23 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/31 15:00:26 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

// int		found_all_paths(t_farm *farm)
// {
// 	static int i = 10;
// 	(void)farm;
// 	i--;
// 	return (i);
// }

void		unvisit_rooms(t_farm *farm)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
}

int		choose_best_paths(t_farm *farm, int **matrice)
{
	int		ret_algo;
	int		ret_backtrack;

	ret_backtrack = -1;
	while (1)
	// while (found_all_paths(farm) > 0)
	{
		while ((ret_algo = algo(farm, matrice)) == SUCCESS)
		{
			printf("in while\n");
			if (ret_backtrack != -1)
			{
				printf("before delete\n");
				delete_first_path(farm, ret_backtrack);
				ret_backtrack = -1;
			}
			if (init_paths(farm) == ERROR || fill_path(farm) == ERROR)
				return (ERROR);
			free_queue(farm);
			fill_reserved(farm);
		}
		printf("ret algo = %d\n", ret_algo);
		if (ret_algo == 0)
		{
			ft_putstr("LANCE BATRACK\n");
			//clean les room visitées par le dernier bfs raté
			unvisit_rooms(farm);
			ret_backtrack = backtrack_paths(farm);
			printf("ret_backtrack: %d\n", ret_backtrack);


			// t_rooms *tmp = farm->rooms;
			// while (tmp)
			// {
			// 	printf("room id: %d - visited: %d - reserved: %d\n", tmp->room_id, tmp->visited, tmp->reserved);
			// 	tmp = tmp->next;
			// }


			if (ret_backtrack == ERROR)
			{
				ft_putstr("BATRACK OVER\n");
				//backtrack n'a aucune salle triple a rendre valide: chemins lineaires tous trouvés
				return (SUCCESS);
			}
		}
	}
	return (SUCCESS);
}
