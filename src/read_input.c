/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:47:08 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/23 16:55:51 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** check_start_end() review all rooms to check if there is a start and end.
*/

static int	check_start_end(int error, t_farm *farm)
{
	int		check_startend;
	t_rooms	*tmp_rooms;

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
** is_line_start_end() tells which line is start (1), or end (2).
*/

int			is_line_start_end(int start_end, char *line)
{
	if (line && ft_strcmp(line, "##start") == 0)
		start_end = 1;
	else if (line && ft_strcmp(line, "##end") == 0)
		start_end = 2;
	return (start_end);
}

/*
** check_empty_line_putstr() returns ERROR if there is an empty line.
** then print the whole farm.
*/

int			check_empty_line_putstr(int error, char *line, int ret)
{
	if (line && ft_strcmp(line, "") == 0)
		error = -1;
	if (ret > 0)
		ft_putendl(line);
	return (error);
}

void		free_when_needed(char *line)
{
	if (line)
		free(line);
}

/*
** read_input() numbers every line (except comments). Calls differents checks,
** read all input and writes it.
*/

int			read_input(t_farm *farm, int line_nb, int error, int start_end)
{
	char		*line;
	int			ret;

	line = NULL;
	ret = 1;
	while (ret != 0)
	{
		free_when_needed(line);
		ret = get_next_line(0, &line);
		error = check_empty_line_putstr(error, line, ret);
		start_end = is_line_start_end(start_end, line);
		if (ret != 0)
			error = check_nb_ants(line_nb, farm, line, error);
		if (line && error == 0 && line_nb > 1 && line[0] != '#')
		{
			if (parse(farm, line, start_end) == ERROR)
				error = -1;
			start_end = 0;
		}
		if (line && line[0] == '#' && line[1] != '#')
			line_nb--;
		line_nb++;
	}
	error = check_start_end(error, farm);
	return (error);
}
