// Header 42

#include <lem_in.h>

// Calculer le nb de coups par sets pour choisir le meilleur set
// nb_ants = nb_tours - length (length = nb de salles entre start et end)
// nb_tours = (nb_ants + sum(length) - (2 * nb_paths)) / nb_paths

// Calculer combien de fourmis on envoie par chemins
// nb_ants = nb_tours - length (length = nb de salles entre start et end)

// Pour chaque chemin, créer un segment [1, 1] (les chiffres sont les id des ants) à incrémenter à chaque tour
// exemple de 5 fourmis: [1, 1], [1, 2], [1, 3], [1, 4], [1, 5], [2, 5]...[5, 5]
// Créer un tableau contenant, pour chaque fourmi, un compteur: commence a 0,
// si la fourmi bouge dune case le compteur sincremente de 1, etc...
// si la fourmi a bouge de 10 case, le compteur est a 10, on regarde dans le tableau
// de path a quel id de salle correspond lindex 10, et on a sa position: l'id de la
// salle dans laquelle elle est, on met un int visited a 1 : la salle est occupee
// si le compteur est egale a la taille du chemin, on ne lincremente plus, la fourmi est
// arrivee

/*
** choose_set()
*/

void	choose_set(t_farm *farm)
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
		tmp = farm->sets[i];
	}
	printf("min: %d\n", min);
	printf("index_min: %d\n", index_min);
}