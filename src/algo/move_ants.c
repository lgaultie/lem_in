/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:02:29 by cmouele           #+#    #+#             */
/*   Updated: 2019/09/11 23:15:16 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

// Créer un tableau contenant, pour chaque fourmi, un compteur: commence a 0,
// si la fourmi bouge dune case le compteur sincremente de 1, etc...
// si la fourmi a bouge de 10 case, le compteur est a 10, on regarde dans le tableau
// de path a quel id de salle correspond lindex 10, et on a sa position: l'id de la
// salle dans laquelle elle est, on met un int visited a 1 : la salle est occupee
// si le compteur est egale a la taille du chemin, on ne lincremente plus, la fourmi est
// arrivee

/*
** send_ants()
*/

/*static int	send_ants(t_farm *farm, int index_of_set)
{
	int		*ants;
	int		i;
	t_paths	*tmp;

	if (!(ants = ft_memalloc(sizeof(int) * farm->ants)))
		return (ERROR);
	i = 0;
	tmp = farm->sets[index_of_set];
	while (tmp)
	{
		printf("ants a envoyer dans le chemin = %d\n", tmp->ants_to_send);
		// la fourmi visite sur une salle du chemin
		// on met la salle d'où elle vient à visited = 0
		// on met la salle où elle est à visited = 1
		// si la fourmi doit aller sur une salle déjà visited, on ne fait rien
		// om imprime
		tmp = tmp->next;
	}
	return (SUCCESS);
}*/

/*
** segment_ants() creates, for each path, a segment with the id of the first
** ant and the id of the last ant.
*/

static void		segment_ants(t_farm *farm, int index_of_set)
{
	t_paths	*tmp;
	int		id_ant;
	int		left_segment;
	int		right_segment;

	tmp = farm->sets[index_of_set];
	id_ant = 1;
	while (tmp)
	{
		left_segment = id_ant;
		right_segment = left_segment + tmp->ants_to_send - 1;
		id_ant = right_segment + 1;
		tmp->left_seg = left_segment;
		tmp->right_seg = right_segment;
		printf("path - left segment: %d, right segment: %d\n", tmp->left_seg, tmp->right_seg);
		tmp = tmp->next;
	}
}

/*
** choose_set() searches for the best set of paths to use (the one with the
** minimum moves number of moves). It returns the index of the optimized set.
** Formula: nb_moves = (nb_ants + sum(length) - (2 * nb_paths)) / nb_paths.
*/

static int	choose_set(t_farm *farm)
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
	printf("choose the set with index %d!\n", index_min);
	farm->nb_moves = min;
	return (index_min);
}

/*
** ants_per_paths() calls choose_set() to find the optimized set of paths. It
** then calculates the number of ants we need to send to each path of the
** optimized set and saves it. Formula: nb_ants = nb_moves - (length - 2). If
** the number of ants sent is different from the original number, we dispatch
** ants randomly in the paths until the original number is reached.
*/

int			ants_per_paths(t_farm *farm)
{
	int		index_of_set;
	int		total_ants_sent;
	t_paths	*tmp;

	index_of_set = choose_set(farm);
	total_ants_sent = 0;
	tmp = farm->sets[index_of_set];
	while (tmp)
	{
		//probleme: avec peu de ants renvoie des nb negatifs
		tmp->ants_to_send = farm->nb_moves - (tmp->length - 2);
		printf("farm->nb_moves = %d, length = %d, ants a envoyer = %d\n", farm->nb_moves, tmp->length, tmp->ants_to_send);
		total_ants_sent += tmp->ants_to_send;
		tmp = tmp->next;
	}
	printf("total de fourmis dans la map = %d\n", farm->ants);
	printf("total de fourmis envoyées dans les chemins = %d\n", total_ants_sent);
	tmp = farm->sets[index_of_set];
	while (tmp)
	{
		if (total_ants_sent < farm->ants)
		{
			printf("on renvoie une fourmi !\n");
			tmp->ants_to_send++;
			total_ants_sent++;
		}
		tmp = tmp->next;
	}
	printf("total de fourmis dans la map = %d\n", farm->ants);
	printf("total de fourmis envoyées dans les chemins = %d\n", total_ants_sent);
	segment_ants(farm, index_of_set);
	/*if (send_ants(farm, index_of_set) == ERROR)
		return (ERROR);*/
	return (SUCCESS);
}
