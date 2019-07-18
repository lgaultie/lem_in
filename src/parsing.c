/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:48:27 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/18 18:26:41 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** add_room: si c'est premiere salle, relie cette new structure à celle
** de la colonie: farm->rooms = new. Si c'est une seconde salle, l'ajoute à
** la suite.
** Initialise les salles.
*/

int			add_room(t_farm *farm, char **tab, int startend)
{
	t_rooms		*tmp;
	t_rooms		*new;
	static int	room_id = 0;

	tmp = farm->rooms;
	if ((new = ft_memalloc(sizeof(t_rooms))) == NULL)
		return (ERROR);
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		new->prev = NULL;
		farm->rooms = new;
	}
	if (!(new->name = ft_strdup(tab[0])))
		return (ERROR);
	new->room_id = room_id;
	new->x_pos = ft_atoi(tab[1]);
	new->y_pos = ft_atoi(tab[2]);
	new->start_end = startend;
	new->next = NULL;
	room_id++;
	return (SUCCESS);
}

/*
** new_link: on créé un new link, farm->rooms->link = new si c'est le premier,
** l'ajoute si c'est un suivant. Pas de prev a initialiser.
** copie le nom du link.
*/

static int	new_link(t_rooms *room, char *name)
{
	t_links	*tmp;
	t_links	*new;

	tmp = room->links;
	if ((new = ft_memalloc(sizeof(t_links))) == NULL)
		return (ERROR);
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		room->links = new;
	if (!(new->name = ft_strdup(name)))
		return (ERROR);
	new->next = NULL;
	return (SUCCESS);
}

/*
** add_link: on indique a qui est collé la salle (far->rooms).
** probleme dans les cas où plusieurs liaisons, y'a des links qui se perdent
*/

int		add_link(t_farm *farm, char **tab)
{
	t_rooms	*tmp;

	tmp = farm->rooms;
	while (tmp)
	{
		if ((ft_strcmp(tmp->name, tab[1])) == 0)
		{
			if (new_link(tmp, tab[0]) == ERROR)
				return (ERROR);
			// printf("dans 1 if --- name = %s		link->name = %s\n", tmp->name, tmp->links->name);
		}
		if ((ft_strcmp(tmp->name, tab[0])) == 0)
		{
			if (new_link(tmp, tab[1]) == ERROR)
				return (ERROR);
			// printf("dans 2 if --- name = %s		link->name = %s\n", tmp->name, tmp->links->name);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/*
** check_format: check si premiere ligne viable = nb de fourmis positif.
** si il y a des espaces dans les noms des salles--> gg wp
** lance le parsing des rooms et links entre rooms.
*/

int		    parse(t_farm *farm, int line_nb, char *line, int start_end)
{
	char		**rooms;
	char		**links;

	if (line_nb == 1)
	{
		farm->ants = ft_atoi(line);
		if (farm->ants <= 0)
			return (ERROR);
	}
	if (line_nb > 1 && ft_strchr(line, ' '))
	{
		farm->total_rooms++;
		if (!(rooms = ft_strsplit(line, ' ')))
			return (ERROR);
		add_room(farm, rooms, start_end);
		ft_free_tab(rooms);
	}
	if (line_nb > 1 && ft_strchr(line, '-') && !(ft_strchr(line, ' ')))
	{
		if (!(links = ft_strsplit(line, '-')))
			return (ERROR);
		add_link(farm, links);
		ft_free_tab(links);
	}
	return (SUCCESS);
}
