# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 16:23:11 by oyagci            #+#    #+#              #
#    Updated: 2016/12/01 16:31:22 by oyagci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= clang
CFLAGS			= -Wall -Wextra -Werror

NAME			= ft_ls

SOURCES_RAW		= main.c ft_ls.c filters.c
SOURCES			= $(SOURCES_RAW)

OBJECTS_RAW		= $(SOURCES:.c=.o)
OBJECTS			= $(OBJECTS_RAW)

LIBS_FOLDER		= -L libft/
LIBS			= -lft
INCLUDES		= -I libft/includes/

.PHONY: all clean fclean re
all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) -o $(NAME) $(SOURCES) $(CFLAGS) $(INCLUDES) $(LIBS_FOLDER) $(LIBS)

%.o: %.c
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
