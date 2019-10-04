/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:13 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 15:41:50 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** init_room() initializes and fills a room.
*/

static int	init_room(t_rooms *new, char **tab, int startend)
{
	static int	room_id = 0;

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
** add_room() creates a new room if this is the first of the list, calls
** init_room() to fill it, and adds it to the list of rooms.
*/

static int	add_room(t_farm *farm, char **tab, int startend)
{
	t_rooms	*tmp;
	t_rooms	*new;

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
	if (init_room(new, tab, startend) == ERROR)
		return (ERROR);
	if (startend == 1)
		farm->start = new;
	if (startend == 2)
		farm->end = new;
	return (SUCCESS);
}

/*
** check_tab_of_three() checks if the tab for room is made of 3 parts, to
** prevent wrong order in the map file. If not, it returns ERROR.
*/

static int	check_tab_of_three(char **rooms)
{
	int	i;

	i = 0;
	while (rooms[i])
		i++;
	if (i != 3)
		return (ERROR);
	return (SUCCESS);
}

/*
** already_exists() checks if the new room uses a name or the coordinates
** already given to another room.
*/

static int	already_exists(char **rm, t_farm *farm)
{
	t_rooms	*tmp;

	if (!(farm->rooms))
		return (SUCCESS);
	if (!ft_isnumber(rm[1]) && !ft_isnumber(rm[2]))
		return (ERROR);
	tmp = farm->rooms;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, rm[0]) == 0)
			return (ERROR);
		if ((tmp->x_pos == ft_atoi(rm[1])) && (tmp->y_pos == ft_atoi(rm[2])))
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/*
** parse_rooms() calls different checking functions to check if the rooms are
** valid.
*/

int			parse_rooms(t_farm *farm, char *line, int start_end)
{
	char	**room;

	farm->total_rooms++;
	if (!(room = ft_strsplit(line, ' ')))
		return (ERROR);
	if ((check_tab_of_three(room) == ERROR) || room[0][0] == 'L' \
	|| (already_exists(room, farm) == ERROR) \
	|| (add_room(farm, room, start_end) == ERROR))
		return (free_tab_error(room));
	ft_free_tab(&room);
	return (SUCCESS);
}
