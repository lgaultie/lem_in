/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:47:08 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/18 19:14:24 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** read_input: line_nb note les lignes par numéro (sauf les comments), pour
** analyser dans le check_format (ex: premiere ligne = nb ant).
** int error existe pour ne pas return directement en cas d'erreur: besoin
** d'imprimer toute la colonie. Si error = 1 -->fin aquisition fourmiliere
** mais traitement normal ensuite!
** start_end -> start = 1, end = 2
*/

int		read_input(t_farm *farm)
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
		ft_putstr(line);
		if (line && ft_strcmp(line, "##start") == 0)
			start_end = 1;
		else if (line && ft_strcmp(line, "##end") == 0)
			start_end = 2;
		if (ret != 0)
			ft_putchar('\n');
		if (line && error == 0 && line[0] != '#')
		{
			if (parse(farm, line_nb, line, start_end) == ERROR)
				error = -1;
			start_end = 0;
		}
		if (line && line[0] == '#' && line[1] != '#')
			line_nb--;
		line_nb++;
		ft_memdel((void**)&line);
	}
	// while (farm->rooms)
	// {
	// 	printf("x_pos = %d, y_pos = %d, name = %s, id = %d, start-end = %d\n", farm->rooms->x_pos, farm->rooms->y_pos, farm->rooms->name, farm->rooms->room_id, farm->rooms->start_end);
	// 	if (farm->rooms->links)
	// 	{
	// 		while (farm->rooms->links)
	// 		{
	// 			printf("\nlinks-name = %s, farm->room->name = %s\n\n", farm->rooms->links->name,  farm->rooms->name);
	// 			farm->rooms->links = farm->rooms->links->next;
	// 		}
	// 	}
	// 	farm->rooms = farm->rooms->next;
	// }
	return (error);
}
