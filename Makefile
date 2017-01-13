# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/05 11:09:45 by lbopp             #+#    #+#              #
#    Updated: 2017/01/12 13:12:41 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = ft_ls 
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/
CC = clang
SRC_NAME = btree.c\
		   btree_long.c\
		   ft_ls.c\
		   long_format.c\
		   long_format2.c\
		   ft_lstsort_insert.c\
		   main.c\
		   opt_to_bits.c\
		   print_tree.c\
		   sort_function.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:.c=.o)
RM = rm -f

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I includes -I libft/includes -lft -L libft

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I includes -I libft/includes

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
