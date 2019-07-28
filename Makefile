# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 14:43:23 by lgaultie          #+#    #+#              #
#    Updated: 2019/07/28 13:23:28 by lgaultie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
CC = @clang
CFLAGS = -Wall -Werror -Wextra -g
LIBDIR = libft
OBJDIR = obj
SRCDIR = src
INC = ./includes/
OBJ = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
#voir GNU 8.3 Functions for File Names
LIB = $(LIBDIR)/libft.a
SRCS =	main.c			\
		read_input.c	\
		parsing.c       \
		parse_rooms.c   \
		parse_links.c	\
		matrice.c       \
		bfs.c           \
		path.c          \
		free.c			\
		free_error.c	\
		unvisit_rooms.c

_GREEN=\e[32m
_PURPLE=\e[35m
_YELLOW=\e[33m
_CYAN=\e[36m
_END=\e[0m

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(_YELLOW)Compiling libft... $(_END)"
	@cd $(LIBDIR) && make
	@printf "$(_YELLOW)Compilation... $(_END)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -I$(INC) -o $(NAME)
	@printf "$(_GREEN)lem_in done [✓]$(_END)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)/*.h
	@$(CC) $(CFLAGS) -c -I$(INC) $< -o $@

$(OBJDIR) :
	@printf "$(_YELLOW)Creating $(_PURPLE)Lem_in$(_YELLOW) obj folder $(_END)"
	@mkdir $@
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
