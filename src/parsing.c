/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:48:27 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/17 18:55:27 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	parse_rooms(char **rooms, t_lem_in *farm)
{
	(void)rooms;
	(void)farm;
	ft_putstr("room\n");
	return ;
}

void	parse_paths(t_lem_in *farm)
{
	(void)farm;
	ft_putstr("path\n");
	return ;
}

/*
** check_format: check si premiere ligne viable = nb de fourmis positif.
** si il y a des espaces dans les noms des salles--> gg wp
*/

int		check_format(t_lem_in *farm, int line_nb, char *line)
{
	char	**rooms;

	if (line_nb == 1)
	{
		farm->ants = ft_atoi(line);
		if (farm->ants <= 0)
			return (ERROR);
	}
	if (line_nb > 1 && ft_strchr(line, ' '))
	{
		farm->total_rooms++;
		if (!(rooms = ft_strsplit(line, ' ')))
			return (ERROR);
		parse_rooms(rooms, farm);
		ft_free_tab(rooms);
	}
	if (line_nb > 1 && ft_strchr(line, '-') && !(ft_strchr(line, ' ')))
		parse_paths(farm);
	return (0);
}
