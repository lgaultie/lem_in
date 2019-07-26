/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:53:07 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/26 12:17:22 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** main() creates farm structure, calls read_input() to read the map, then
** frees it.
*/

int		main(void)
{
	int			line_nb;
	int			error;
	t_farm		*farm;

	line_nb = 1;
	error = 0;
	if (!(farm = ft_memalloc(sizeof(t_farm))) \
		|| read_input(farm, line_nb, error, error) == ERROR)
		return (free_farm_error(farm));
	free_farm(farm);
	return (FAILURE);
}
