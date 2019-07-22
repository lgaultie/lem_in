/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:51:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/22 16:34:47 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
#include <stdio.h>

# define SUCCESS 1
# define FAILURE 0
# define ERROR -1
# define ERROR_MSG "ERROR"

typedef struct			s_queue
{
	int					id;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_paths
{
	int					id_ant;
	int					length;
	int					*path;
	struct s_paths		*next;
}						t_paths;

typedef struct			s_links
{
	struct s_links      *next;
	char                *name;
}						t_links;

typedef struct			s_rooms
{
	char				*name;
	t_links				*links;
	int					room_id;
	int					x_pos;
	int					y_pos;
	int					start_end;
	int					visited;
	int					reserved;
	int					layer;
	struct s_rooms		*prev;
	struct s_rooms		*next;
	struct s_rooms		*parent;
}						t_rooms;

typedef struct			s_farm
{
	int					ants;
	int					total_rooms;
	t_queue				*queue;
	t_rooms				*rooms;
	t_paths				*paths;
}						t_farm;

int		read_input(t_farm *farm, int line_nb, int error, int start_end);
int     check_nb_ants(int line_nb, t_farm *farm, char *line);
int		parse(t_farm *farm, char *line, int start_end);
void	free_farm(t_farm *farm);
void	free_rooms(t_rooms *rooms);
int 	free_farm_error(t_farm *farm);
int		free_tab_error(char **links);
int		parse_rooms(t_farm *farm, char *line, int start_end);
int		parse_links(t_farm *farm, char *line);
int		bfs(t_farm *farm);

#endif
