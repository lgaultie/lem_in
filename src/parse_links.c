/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:08:32 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/22 16:11:32 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

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

int			parse_links(t_farm *farm, char *line)
{
	char		**link;

	if (ft_strchr(line, '-'))
	{
		if (!(link = ft_strsplit(line, '-')))
			return (ERROR);
		if (add_link(farm, link) == ERROR)
			return (free_tab_error(link));
		ft_free_tab(link);
	}
	return (SUCCESS);
}
