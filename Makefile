# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 14:43:23 by lgaultie          #+#    #+#              #
#    Updated: 2019/07/31 11:23:28 by lgaultie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
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
		free_error.c					\
		$(PARS_DIR)/read_input.c		\
		$(PARS_DIR)/parsing.c			\
		$(PARS_DIR)/rooms.c				\
		$(PARS_DIR)/links.c				\
		$(ALGO_DIR)/bfs.c				\
		$(ALGO_DIR)/queue.c				\
		$(ALGO_DIR)/matrice.c			\
		$(ALGO_DIR)/choose_paths.c      \
		$(ALGO_DIR)/path.c              \
		$(ALGO_DIR)/manage_rooms.c

OBJ = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
#voir GNU 8.3 Functions for File Names

_GREEN=\e[32m
_PURPLE=\e[35m
_YELLOW=\e[33m
_CYAN=\e[36m
_END=\e[0m

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(_YELLOW)Compiling libft... $(_END)"
	@make -C $(LIBDIR)
	@printf "$(_YELLOW)Compilation... $(_END)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -I$(INC) -o $(NAME)
	@printf "$(_GREEN)lem_in done [✓]$(_END)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
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
