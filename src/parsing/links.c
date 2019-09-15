/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:40:05 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/04 16:42:16 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** new_link() creates a new link if this is the first of the list, fills it,
** and adds it to the list of links.
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
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		room->links = new;
	if (!(new->name = ft_strdup(name)))
		return (ERROR);
	room->nb_links++;
	new->next = NULL;
	return (SUCCESS);
}

/*
** add_link() checks the two rooms of a link, in two ways, and calls new_link()
** to add them to their respective list of links.
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
** check_valid_room_name() checks if the link describes two known rooms.
** success_1 checks the name of the first room, success_2 the second.
*/

static int	check_valid_room_name(char **links, t_farm *farm)
{
	t_rooms		*tmp;
	int			success_1;
	int			success_2;

	success_1 = 0;
	success_2 = 0;
	tmp = farm->rooms;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, links[0]) == 0)
			success_1 = 1;
		if (ft_strcmp(tmp->name, links[1]) == 0)
			success_2 = 1;
		tmp = tmp->next;
	}
	if (success_1 == 0 || success_2 == 0)
		return (ERROR);
	return (SUCCESS);
}

/*
** parse_links() calls different checking functions to check if the links are
** valid.
*/

int			parse_links(t_farm *farm, char *line)
{
	char		**link;

	if (ft_strchr(line, '-'))
	{
		if (!(link = ft_strsplit(line, '-')))
			return (ERROR);
		if (check_valid_room_name(link, farm) == ERROR \
		|| add_link(farm, link) == ERROR)
		{
			ft_putstr("nameee\n");
			return (free_tab_error(link));
		}
		ft_free_tab(&link);
	}
	return (SUCCESS);
}
