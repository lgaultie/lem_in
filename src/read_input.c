/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:47:08 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/17 18:58:36 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** read_input: line_nb note les lignes par numéro (sauf les comments), pour
** analyser dans le check_format (ex: premiere ligne = nb ant).
** int error existe pour ne pas return directement en cas d'erreur: besoin
** d'imprimer toute la colonie. Si error = 1 -->fin aquisition fourmiliere
** mais traitement normal ensuite!
** start_end -> start = 1, end = 2  : faudrait stocker pour verifier la ligne
** d'avant, au lieu de putstr direct en fait
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
		if (ret != 0)
			ft_putchar('\n');
		if (ret > 0 && error == 0 && line[0] != '#')
		{
			if (check_format(farm, line_nb, line) == ERROR)
				error = -1;
		}
		if (ret > 0 && line[0] == '#' && line[1] != '#')
			line_nb--;
		line_nb++;
		ft_memdel((void**)&line);
	}
	return (error);
}
