/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:47:08 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/22 18:24:11 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** check_ants() checks if the first line is a number. If it is, this is the
** number of ants in the farm. If not, it returns ERROR.
*/

static int	check_nb_ants(int line_nb, t_farm *farm, char *line, int error)
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
** is_start_end() tells which line is start (1), and end (2).
*/

static int	is_start_end(int start_end, char *line)
{
	if (line && ft_strcmp(line, "##start") == 0)
		start_end = 1;
	else if (line && ft_strcmp(line, "##end") == 0)
		start_end = 2;
	return (start_end);
}

/*
** check_line() prints the line, and checks if we have an empty line. If that
** is the case, it returns ERROR.
*/

static int	check_line(char *line, int error)
{
	if (line && ft_strcmp(line, "") == 0)
		error = -1;
	ft_putendl(line);
	return (error);
}

/*
** calculate_line_nb() adjusts according to comments or commands the number
** of the line
*/

static int	calculate_line_nb(char *line, int line_nb, t_farm *farm)
{
	if (line && line[0] == '#' && line_nb > 0 && farm->ants < 1)
	{
		line_nb--;
		if (line_nb == 0)
			line_nb++;
	}
	else
		line_nb++;
	return (line_nb);
}

/*
** read_input() reads every line of the map file, except comments, then calls
** different checking functions to check if the map is valid.
*/

int			read_input(t_farm *farm, int line_nb, int error, int start_end)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = 1;
	while (ret != 0)
	{
		ft_memdel((void*)&line);
		ret = get_next_line(0, &line);
		if (ret != 0)
		{
			error = check_line(line, error);
			start_end = is_start_end(start_end, line);
			error = check_nb_ants(line_nb, farm, line, error);
			if (line && error == 0 && line_nb > 1 && line[0] != '#')
			{
				if (parse(farm, line, start_end) == ERROR)
					error = -1;
				start_end = 0;
			}
			line_nb = calculate_line_nb(line, line_nb, farm);
		}
	}
	error = check_start_end(error, farm);
	return (error);
}
