/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:47:08 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/19 13:38:13 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int  check_input(t_farm *farm)
{
    int     error;
    int     check_startend;
    t_rooms *tmp_rooms;

    error = 0;
    check_startend = 0;
    tmp_rooms = farm->rooms;
    while (tmp_rooms)
    {
        if (tmp_rooms->start_end == 1 || tmp_rooms->start_end == 2)
            check_startend++;
        tmp_rooms = tmp_rooms->next;
    }
    if (check_startend != 2)
        error = -1;
    return (error);
}

/*
** read_input: line_nb note les lignes par numéro (sauf les comments), pour
** analyser dans le check_format (ex: premiere ligne = nb ant).
** int error existe pour ne pas return directement en cas d'erreur: besoin
** d'imprimer toute la colonie. Si error = 1 -->fin aquisition fourmiliere
** mais traitement normal ensuite!
** start_end -> start = 1, end = 2
** attention dans le cas de ##start et ##end a la suite, start va etre
** ignoré, il n'existera pas -->probleme pour l'algo
*/

int		    read_input(t_farm *farm)
{
	int			ret;
	char		*line;
	int			line_nb;
	int			error;
	int			start_end;

	start_end = 0;
	error = 0;
	ret = 1;
	line_nb = 1;
	line = NULL;
	while (ret != 0)
	{
		if (line)
			free(line);
		ret = get_next_line(0, &line);
		ft_putendl(line);
		if (line && ft_strcmp(line, "##start") == 0)
			start_end = 1;
		else if (line && ft_strcmp(line, "##end") == 0)
			start_end = 2;
		if (line_nb == 1)
		    error = check_ants(farm, line);
		if (line && error == 0 && line[0] != '#')
		{
			if (parse(farm, line, start_end) == ERROR)
				error = -1;
			start_end = 0;
		}
		if (line && line[0] == '#' && line[1] != '#')
			line_nb--;
		line_nb++;
		ft_memdel((void**)&line);
	}
    error = check_input(farm);

	/*while (farm->rooms)
    {
        printf("x_pos = %d, y_pos = %d, name = %s, id = %d, start-end = %d\n", farm->rooms->x_pos, farm->rooms->y_pos, farm->rooms->name, farm->rooms->room_id, farm->rooms->start_end);
        if (farm->rooms->links)
        {
            while (farm->rooms->links)
            {
                printf("links-name = %s\n", farm->rooms->links->name);
                farm->rooms->links = farm->rooms->links->next;
            }
        }
        farm->rooms = farm->rooms->next;
	}*/
	return (error);
}
