# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmouele <cmouele@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 09:48:35 by cmouele           #+#    #+#              #
#    Updated: 2019/10/02 10:11:12 by lgaultie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = @clang
CFLAGS = -Wall -Werror -Wextra
SRCS = ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strdup.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_atoi_long.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_itoa.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstadd.c \
	ft_lstaddend.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_fibonacci.c \
	ft_is_prime.c \
	ft_recursive_factorial.c \
	ft_recursive_power.c \
	ft_sqrt.c \
	ft_sqrt_rounded.c \
	get_next_line.c \
	get_next_line_custom.c \
	ft_swap.c \
	ft_free_tab.c \
	ft_strjoinfree.c \
	ft_lstendadd.c \
	ft_strrealloc.c \
	ft_lstprintstr.c \
	ft_display_array.c \
	ft_intlen.c \
	ft_strndup.c \
	ft_isnumber.c
OBJ = $(SRCS:.c=.o)
HEADER = .

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HEADER)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

.PHONY: clean fclean

re: fclean all
