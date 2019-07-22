/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:01:36 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/02 13:37:52 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int  matrice_fill(t_farm *farm, int **matrice)
{
    t_rooms *room;
    t_rooms *room_bis;
    t_links *links;

    room = farm->rooms;
    while (room != NULL)
    {
        links = room->links;
        while (links != NULL)
        {
            room_bis = farm->rooms;
            while (room_bis != NULL)
            {
                if (ft_strcmp(room_bis->name, links->name) == 0)
                    matrice[room->room_id][room_bis->room_id] = 1;
                room_bis = room_bis->next;
            }
            links = links->next;
        }
        room = room->next;
    }
	return (SUCCESS);
}

int         **matrice_create(t_farm *farm)
{
	int i;
	int j;
	int total_rooms;
	int **matrice;

    i = 0;
    j = 0;
	total_rooms = farm->total_rooms;
    matrice = (int**)malloc(sizeof(int*) * total_rooms);
    if (matrice == NULL)
        return (NULL);
    while (i < total_rooms)
    {
        matrice[i] = (int*)malloc(sizeof(int) * total_rooms);
        if (matrice[i] == NULL)
            return (NULL);
        ft_bzero(matrice[i], sizeof(int) * total_rooms);
        i++;
    }
    matrice_fill(farm, matrice);
    // TMP
    printf("matrice:\n");
    int k, l;
    k = 0;
    while (k < total_rooms)
    {
        l = 0;
        while (l < total_rooms)
        {
            printf("%d ", matrice[k][l]);
            l++;
        }
        printf("\n");
        k++;
    }
    // END TMP
    if (init_paths(farm) == ERROR)
        return (NULL);
    while (j < farm->ants)
    {
        if (algo(farm, matrice) == ERROR || fill_path(farm) == ERROR)
            return (NULL);
        reset_bfs(farm);
        j++;
    }
    // TMP
    t_paths *path = farm->paths;
    int m = 0;
    while (path != NULL)
    {
        printf("ant number %d - path: ", path->id_ant);
        while (m < path->length)
        {
            printf("%d", path->path[m]);
            m++;
        }
        printf("\n");
        path = path->next;
    }
    // END TMP
	return (matrice);
}
