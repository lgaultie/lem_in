/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:48:27 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/19 13:10:14 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** add_room: si c'est premiere salle, relie cette new structure à celle
** de la colonie: farm->rooms = new. Si c'est une seconde salle, l'ajoute à
** la suite.
** Initialise les salles.
*/

static int	add_room(t_farm *farm, char **tab, int startend)
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

static int	add_link(t_farm *farm, char **tab)
{
	t_rooms	*tmp;

	tmp = farm->rooms;
	while (tmp)
	{
		if ((ft_strcmp(tmp->name, tab[1])) == 0)
		{
			if (new_link(tmp, tab[0]) == ERROR)
				return (ERROR);
		}
		if ((ft_strcmp(tmp->name, tab[0])) == 0)
		{
			if (new_link(tmp, tab[1]) == ERROR)
				return (ERROR);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/*
** check_tab_of_three: check if the tab for room is made of 3 parts, if it is
** not, returns ERROR. Prevents wrong rooms such as: "start 1 2 3 4 5" or
** wrong links such as: "3-4 1".
*/

int			check_tab_of_three(char **rooms)
{
	int		i;

	i = 0;
	while (rooms[i])
		i++;
	if (i != 3)
		return (ERROR);
	return (SUCCESS);
}

/*
** check_ants() checks if the first line is a number. If it is, this is the
** number of ants in the farm. If not, it returns ERROR.
*/

int         check_ants(t_farm *farm, char *line)
{
    int i = 0;

    while (line[i])
    {
        if (!(ft_isdigit(line[i])))
            return (ERROR);
        i++;
    }
    farm->ants = ft_atoi(line);
    if (farm->ants <= 0)
        return (ERROR);
    return (SUCCESS);
}

/*
** check_format: checks data and calls room and links parsing.
** si il y a des espaces dans les noms des salles--> je lance error
*/

int		    parse(t_farm *farm, char *line, int start_end)
{
	char		**room;
	char		**link;

	if (ft_strchr(line, ' '))
	{
		farm->total_rooms++;
		if (!(room = ft_strsplit(line, ' ')))
			return (ERROR);
		if ((check_tab_of_three(room) == ERROR) || room[0][0] == 'L' \
		|| (add_room(farm, room, start_end) == ERROR))
			return (free_tab_error(room));
		ft_free_tab(room);
	}
	else if (ft_strchr(line, '-'))
	{
		if (!(link = ft_strsplit(line, '-')))
			return (ERROR);
		if (add_link(farm, link) == ERROR)
			return (free_tab_error(link));
		ft_free_tab(link);
	}
	return (SUCCESS);
}
