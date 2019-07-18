/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:53:07 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/18 16:34:45 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** main: crée structure pour la colonie, lance le read, free structure.
*/

int		main(void)
{
	t_farm	*farm;

	if (!(farm = ft_memalloc(sizeof(t_farm))) || read_input(farm) == -1)
    {
        ft_putendl(ERROR_MSG);
	    return (ERROR);
    }
	free_farm(farm);
	return (FAILURE);
}
