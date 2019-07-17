/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_farm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:57:37 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/02 12:40:30 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int     add_room(t_farm *farm, char **tab, int startend)
{
    t_rooms     *tmp;
    t_rooms     *new;
    static int  room_id = 0;

    tmp = farm->rooms;
    if ((new = (t_rooms*)malloc(sizeof(t_rooms))) == NULL)
        return (ERROR);
    ft_bzero(new, sizeof(t_rooms));
    if (tmp != NULL)
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }
    else
        farm->rooms = new;
    new->room = tab[0];
    new->room_id = room_id;
    new->x_pos = ft_atoi(tab[1]);
    new->y_pos = ft_atoi(tab[2]);
    new->start_end = startend;
    new->next = NULL;
    room_id++;
    return (SUCCESS);
}

static int  new_link(t_rooms *room, char *name)
{
    t_links *tmp;
    t_links *new;

    tmp = room->links;
    if ((new = (t_links*)malloc(sizeof(t_links))) == NULL)
        return (ERROR);
    ft_bzero(new, sizeof(t_links));
    if (tmp != NULL)
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
    }
    else
        room->links = new;
    new->name = name;
    new->next = NULL;
    return (SUCCESS);
}

int         add_link(t_farm *farm, char **tab)
{
    t_rooms *tmp;

    tmp = farm->rooms;
    while (tmp != NULL)
    {
        if ((ft_strcmp(tmp->room, tab[0])) == 0)
            if (new_link(tmp, tab[1]) == ERROR)
                return (ERROR);
        if ((ft_strcmp(tmp->room, tab[1])) == 0)
            if (new_link(tmp, tab[0]) == ERROR)
                return (ERROR);
        tmp = tmp->next;
    }
    return (SUCCESS);
}
