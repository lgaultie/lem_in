# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 21:15:02 by lgaultie          #+#    #+#              #
#    Updated: 2018/12/20 17:51:41 by lgaultie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = @clang
CFLAGS = -Wall -Werror -Wextra
SRCS =	ft_atoi.c			\
		ft_strlen.c			\
		ft_strcmp.c			\
		ft_strdup.c			\
		ft_strcpy.c			\
		ft_strncpy.c		\
		ft_memset.c			\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memccpy.c		\
		ft_memmove.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strcat.c			\
		ft_strncat.c		\
		ft_strlcat.c		\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_strstr.c			\
		ft_strnstr.c		\
		ft_strncmp.c		\
		ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_putchar.c		\
		ft_putstr.c			\
		ft_strclr.c			\
		ft_strnew.c			\
		ft_strequ.c			\
		ft_memalloc.c		\
		ft_memdel.c			\
		ft_strdel.c			\
		ft_striter.c		\
		ft_striteri.c		\
		ft_strmap.c			\
		ft_strmapi.c		\
		ft_strnequ.c		\
		ft_strsub.c			\
		ft_strjoin.c		\
		ft_strjoinfree.c	\
		ft_strtrim.c		\
		ft_strsplit.c		\
		ft_putnbr.c			\
		ft_putendl.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\
		ft_itoa.c			\
		ft_lstnew.c			\
		ft_lstdelone.c		\
		ft_lstdel.c			\
		ft_lstadd.c			\
		ft_lstiter.c		\
		ft_lstmap.c			\
		ft_lstendadd.c		\
		ft_sqrt.c			\
		ft_strrealloc.c		\
		ft_lstprintstr.c	\
		ft_display_array.c	\
		ft_intlen.c			\
		ft_strndup.c		\
		get_next_line.c

OBJ = $(SRCS:.c=.o)
HEADER = .

_GREEN=\e[32m
_PURPLE=\e[35m
_YELLOW=\e[33m
_CYAN=\e[36m
_END=\e[0m

all: $(NAME)

$(NAME):
	@printf "$(_YELLOW)compiling libft..$(_END)\n"
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HEADER)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)
	@printf "$(_PURPLE)libft $(_YELLOW)cleaned.. $(_END)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(_CYAN)libft fcleaned$(_END)\n"

re: fclean all
