# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 14:43:23 by lgaultie          #+#    #+#              #
#    Updated: 2019/10/04 16:30:01 by lgaultie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = @clang
CFLAGS = -Wall -Werror -Wextra -g
LIBDIR = libft
LIB = $(LIBDIR)/libft.a
OBJDIR = obj
SRCDIR = src
INC = ./includes/
ALGO_DIR = algo
PARS_DIR = parsing

SRCS =	main.c							\
		free.c							\
		free_two.c						\
		free_error.c					\
		print.c							\
		$(PARS_DIR)/read_input.c		\
		$(PARS_DIR)/parsing.c			\
		$(PARS_DIR)/rooms.c				\
		$(PARS_DIR)/links.c				\
		$(ALGO_DIR)/bfs.c				\
		$(ALGO_DIR)/bfs_two.c			\
		$(ALGO_DIR)/queue.c				\
		$(ALGO_DIR)/matrice.c			\
		$(ALGO_DIR)/choose_paths.c      \
		$(ALGO_DIR)/calc_sets.c     	\
		$(ALGO_DIR)/path.c              \
		$(ALGO_DIR)/delete_path.c       \
		$(ALGO_DIR)/visit_rooms.c       \
		$(ALGO_DIR)/path_set.c          \
		$(ALGO_DIR)/backtrack.c         \
		$(ALGO_DIR)/sets.c              \
		$(ALGO_DIR)/print_ants.c

OBJ = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
#voir GNU 8.3 Functions for File Names

_GREEN=\e[32m
_PURPLE=\e[35m
_BLUE=\e[34m
_YELLOW=\e[33m
_CYAN=\e[36m
_RED=\e[31m
_END=\e[0m

all: $(NAME)
	@printf "$(_PURPLE)                                 _      _       $(_END)   __$(_PURPLE)  _                   _ _   _      _      \n"
	@printf "$(_CYAN)  ___ _ __ ___   ___  _   _  ___| | ___( )___   $(_END)  / /$(_CYAN) | | __ _  __ _ _   _| | |_(_) ___( )___  \n"
	@printf "$(_GREEN) / __| '_ ' _ \ / _ \| | | |/ _ \ |/ _ \// __| $(_END)  / /$(_GREEN)  | |/ _' |/ _' | | | | | __| |/ _ \// __| \n"
	@printf "$(_YELLOW)| (__| | | | | | (_) | |_| |  __/ |  __/ \__ \ $(_END) / / $(_YELLOW)  | | (_| | (_| | |_| | | |_| |  __/ \__ \ \n"
	@printf "$(_PURPLE) \___|_| |_| |_|\___/ \__,_|\___|_|\___| |___/ $(_END)/_/  $(_PURPLE)  |_|\__, |\__,_|\__,_|_|\__|_|\___| |___/ \n"
	@printf "$(_PURPLE)                                                         |___/                                 \n"
	@printf "$(_CYAN) _                      _       \n"
	@printf "$(_CYAN)| | ___ _ __ ___       (_)_ __  \n"
	@printf "$(_GREEN)| |/ _ \ '_ ' _ \ _____| | '_ \  \n"
	@printf "$(_YELLOW)| |  __/ | | | | |_____| | | | |\n"
	@printf "$(_PURPLE)|_|\___|_| |_| |_|     |_|_| |_|\n"
	@printf " $(_END)\n"

$(NAME): $(OBJ)
	@printf "$(_YELLOW)Compiling libft... $(_END)"
	@make -C $(LIBDIR)
	@printf "$(_YELLOW)Compilation... $(_END)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -I$(INC) -o $(NAME)
	@printf "$(_GREEN)lem_in done [✓]$(_END)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c includes/lem_in.h
	@$(CC) $(CFLAGS) -c -I$(INC) $< -o $@

$(OBJDIR) :
	@printf "$(_YELLOW)Creating $(_PURPLE)Lem_in$(_YELLOW) obj folder $(_END)"
	@mkdir $@ $@/$(ALGO_DIR) $@/$(PARS_DIR)
	@printf "$(_CYAN)done$(_END)\n"

$(OBJ) : | $(OBJDIR)
#voir GNU make 4.3 Types of Prerequisites

clean:
	@printf "$(_YELLOW)clean... $(_END)"
	@cd $(LIBDIR) && make clean
	@rm -rf $(OBJDIR)
	@printf "$(_CYAN)done$(_END)\n"

fclean: clean
	@printf "$(_YELLOW)fclean... $(_END)"
	@cd $(LIBDIR) && make fclean
	@rm -rf $(NAME)
	@printf "$(_CYAN)done $(_END)\n"

re: fclean all clean

.PHONY: clean fclean all re
