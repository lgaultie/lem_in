// Header 42

#include <lem_in.h>

// Calculer le nb de coups par sets pour choisir le meilleur set
// nb_ants = nb_tours - length (length = nb de salles entre start et end)
// nb_tours = (nb_ants + sum(length) - (2 * nb_paths)) / nb_paths

// Calculer combien de fourmis on envoie par chemins
// nb_ants = nb_tours - length (length = nb de salles entre start et end)

// Créer un tableau contenant, pour chaque fourmi, un compteur: commence a 0,
// si la fourmi bouge dune case le compteur sincremente de 1, etc...
// si la fourmi a bouge de 10 case, le compteur est a 10, on regarde dans le tableau
// de path a quel id de salle correspond lindex 10, et on a sa position: l'id de la
// salle dans laquelle elle est, on met un int visited a 1 : la salle est occupee
// si le compteur est egale a la taille du chemin, on ne lincremente plus, la fourmi est
// arrivee

/*
** choose_set() searches best set to use, the one with minimum moves (int min) :
** returns index_min the index of this optimized set.
*/

int		choose_set(t_farm *farm)
{
	int		i;
	int		length;
	int		nb_moves;
	int		min;
	int		index_min;
	t_paths	*tmp;

	i = 0;
	length = 0;
	nb_moves = 0;
	min = 0;
	index_min = 0;
	tmp = farm->sets[i];
	while (i < farm->nb_paths)
	{
		length = 0;
		while (tmp)
		{
			length += farm->sets[i]->length;
			tmp = tmp->next;
		}
		if (farm->ants >= i + 1)
			nb_moves = (farm->ants + length - (2 * (i + 1))) / (i + 1);
		printf("nb_moves: %d\n", nb_moves);
		printf("length: %d\n", length);
		if (min == 0 || nb_moves < min)
		{
			min = nb_moves;
			index_min = i;
		}
		i++;
		if (i < farm->nb_paths)
			tmp = farm->sets[i];
	}
	printf("min: %d\n", min);
	printf("chose the %d paths set !!\n", index_min + 1);
	farm->nb_moves = min;
	return (index_min);
}

// // Créer un tableau contenant, pour chaque fourmi, un compteur: commence a 0,
// // si la fourmi bouge dune case le compteur sincremente de 1, etc...
// // si la fourmi a bouge de 10 case, le compteur est a 10, on regarde dans le tableau
// // de path a quel id de salle correspond lindex 10, et on a sa position: l'id de la
// // salle dans laquelle elle est, on met un int visited a 1 : la salle est occupee
// // si le compteur est egale a la taille du chemin, on ne lincremente plus, la fourmi est
// // arrivee
// void		send_ants(t_farm *farm)
// {
// 	int		*ants;
// 	int		arrived;
	
// 	arrived = 0;
// 	if (!(ants = ft_memalloc(sizeof(int) * farm->ants)))
// 		return ;
// 	while (arrived < farm->ants)
// 	{
// 		//si ants[x] = salle end, alors arrived++
// 	}
// }

/*
** how_much_ants_per_paths() calculates how many ants we need to send to each paths
** of the set using this formula: nb_ants = nb_moves - length + 1
** save in path->ants_to_send the numbers of ants to end to each paths
*/

void		how_much_ants_per_paths(t_farm *farm)
{
	int		index_of_set;
	t_paths	*tmp;

	index_of_set = choose_set(farm);
	tmp = farm->sets[index_of_set];
	while (tmp)
	{
		//probleme: avec peu de ants renvoie des nb negatifs
		tmp->ants_to_send = farm->nb_moves - (tmp->length - 2);
		printf("farm->nb_moves = %d, length = %d, ants a envoyer = %d\n", farm->nb_moves, tmp->length, tmp->ants_to_send);
		tmp = tmp->next;
	}
	// send_ants(farm);
	printf("nb_ants = %d\n",farm->ants);
}
