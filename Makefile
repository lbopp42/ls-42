# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/05 11:09:45 by lbopp             #+#    #+#              #
#    Updated: 2017/01/05 12:48:15 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = ft_ls 
CFLAGS = -Wall -Werror -Wextra -g -I include/ 
LIBFT = libft/
CC = clang
CFLAGS = -Wall -Werror -Wextra
SRC_NAME = btree.c\
	dir_list.c\
	ft_lstsort_insert.c\
	sort_function.c\
	btreemain.c\
	ft_ls.c\
	main.c\
	treatment_opt.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:.c=.o)
RM = rm -f

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I includes -I libft/includes -lft -L libft

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I includes

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
