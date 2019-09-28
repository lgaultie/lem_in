/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:44:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/04 16:33:50 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** parse() checks data for rooms and links, calls parse_rooms() and
** parse_links(). 'order' equals 2 when parsing rooms, and 3 when
** parsing links, to prevent wrong order during the check.
*/

int	parse(t_farm *farm, char *line, int start_end)
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
