/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:51:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/10/04 16:30:50 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
#include <stdio.h> // TMP

# define SUCCESS		1
# define FAILURE		0
# define ERROR			-1
# define DEADEND		-3
# define ERROR_MSG		"ERROR"

typedef struct			s_queue
{
	int					id;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_paths
{
	int					length;
	int					ants_to_send;
	int					left_seg;
	int					right_seg;
	int					*path;
	struct s_paths		*prev;
	struct s_paths		*next;
}						t_paths;

typedef struct			s_sets
{
	int					size;
	int					ants_sent;
	t_paths				*paths;
	int					moves;
	struct s_sets		*next;
}						t_sets;

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
	int					to_reserve;
	int					nb_links;
	int					layer;
	struct s_rooms		*prev;
	struct s_rooms		*next;
	struct s_rooms		*parent;
	t_paths				*path;
}						t_rooms;

typedef struct			s_farm
{
	int					nb_moves;
	int					nb_paths;
	int					nb_sets;
	int					ants;
	int					visu;
	int					total_rooms;
	int					size_released;
	int					*released_rooms;
	t_rooms				**all_rooms;
	t_queue				*queue;
	t_rooms				*rooms;
	t_rooms				*start;
	t_rooms				*end;
	t_paths				*paths;
	t_paths				*found_paths;
	t_sets				*sets;
}						t_farm;

int		read_input(t_farm *farm, int line_nb, int error, int start_end);
int		parse(t_farm *farm, char *line, int start_end);
int		parse_rooms(t_farm *farm, char *line, int start_end);
int		parse_links(t_farm *farm, char *line);
int		**matrice_create(t_farm *farm, int i);
int		algo(t_farm *farm, int **matrice);
int		queue(t_farm *farm, int room_id);
int		unqueue(t_farm *farm);
void 	free_matrice(t_farm *farm, int **matrice);
void	free_rooms(t_rooms *rooms);
void	free_queue(t_farm *farm);
void	free_paths(t_farm *farm);
int 	free_farm_error(t_farm *farm);
int		free_tab_error(char **tab);
int		init_paths(t_farm *farm);
int		fill_path(t_farm *farm);
int		save_path(t_farm *farm, t_paths *paths);
int		in_released_rooms(t_farm *farm, int id);
int		backtrack_paths(int block, t_farm *farm);
void	delete_path(t_sets *set, t_paths **src, t_paths *path);
int		unvisit(int *path, int length, t_farm *farm, int id_room);
int		find_paths(t_farm *farm, int **matrice);
int		check_paths(t_farm *farm);
int		path_to_delete(t_farm *farm, int id_room);
void	free_sets(t_farm *farm);
void	free_found_paths(t_farm *farm);
int		allocate_sets(t_farm *farm);
int		send_ants(t_farm *farm, t_paths *paths);
void	choose_set(t_farm *farm);
void	fill_reserved(t_farm *farm);
int		init_sets(t_farm *farm);
int		calc_moves(int nb_moves, int size, int len, t_farm *farm);
int		calc_length(t_paths *tmp, int length);
//print functions
void	print_tab_paths(t_farm *farm);
void	print_free_rooms(t_farm *farm);
void	print_paths(t_farm *farm);
void	display_sets(t_farm *farm);
void	print_chosen_paths(t_farm *farm, t_sets *set);
void	print_nb_moves(int i, int nb_moves);

#endif
