/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:53:07 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/17 17:59:53 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <stdio.h>

int		check_format(t_lem_in *farm, int line_nb, char *line)
{
	char	**rooms;

	if (line_nb == 1)
	{
		farm->ants = ft_atoi(line);
		if (farm->ants <= 0)
			return (ERROR);
	}
	if (line_nb > 1 && ft_strchr(line, ' '))									//si il y a des espaces dans les noms des salles--> gg wp
	{
		farm->total_rooms++;
		if (!(rooms = ft_strsplit(line, ' ')))
			return (ERROR);
		//copier dans la structure now.
		ft_free_tab(rooms);
	}
	return (0);
}

int		read_input(t_lem_in *farm)
{
	int			ret;
	char		*line;
	int			line_nb;
	int			error;
	// int			start_end;

	char	buf[100];

	(void)farm;
	error = 0;
	ret = 1;
	line_nb = 1;
	line = NULL;
	while (ret != 0)
	{
		// if (line)
		// 	free(line);

		ret = read(0, buf, 100);
		write(1, buf, ret);
		// ret = get_next_line(0, &line);
		ft_putnbr(ret);
		// ft_putstr(line);
		ft_putchar('\n');
		// ft_putstr("ligne imprimée\n");
		// if (error == 0 && line[0] != '#')										//si error = 1-->fin aquisition fourmiliere mais traitement normal ensuite
		// {
		// 	if (check_format(farm, line_nb, line) == ERROR)
		// 		error = -1;														//je return pas direct pour pouvoir imprimer toute la colonie
		// }
		// if (line[0] == '#' && line[1] != '#')									//si c'est un comment on compte pas la ligne
		// 	line_nb--;
		// line_nb++;
		ft_memdel((void**)&line);
	}
	// return (-1);
	return (error);
}

int		main(void)
{
	t_lem_in	*farm;

	if (!(farm = ft_memalloc(sizeof(t_lem_in))))
		return (-1);
	if (read_input(farm) == -1)
		ft_putstr("ERROR\n");
	free(farm);
	return (0);
}
