/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:48:27 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/23 16:55:55 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** check_ants() checks if the first line is a number. If it is, this is the
** number of ants in the farm. If not, it returns ERROR.
*/

int			check_nb_ants(int line_nb, t_farm *farm, char *line, int error)
{
	int i;

	i = 0;
	if (line_nb == 1 && line[0] != '#')
	{
		farm->ants = ft_atoi(line);
		if (farm->ants <= 0)
			return (ERROR);
	}
	return (error);
}

/*
** parse() checks data for rooms and links, calls parse_rooms() and
** parse_links(). Static int order equals 2 when parsing rooms, and 3 when
** parsing links to prevent wrong order in the map file.
*/

int			parse(t_farm *farm, char *line, int start_end)
{
	static int	order = 1;

	if (!(ft_strchr(line, ' ')) && !(ft_strchr(line, '-')))
		return (ERROR);
	if (ft_strchr(line, ' '))
	{
		if (order == 3)
			return (ERROR);
		order = 2;
		if (parse_rooms(farm, line, start_end) == ERROR)
			return (ERROR);
	}
	else if (ft_strchr(line, '-'))
	{
		if (order == 1)
			return (ERROR);
		order = 3;
		if (parse_links(farm, line) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
