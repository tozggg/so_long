# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 14:11:44 by taejkim           #+#    #+#              #
#    Updated: 2021/10/21 15:55:13 by taejkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

INCDIR = ./include/
SRCDIR = ./src/
LIBDIR = ./libft/
MLXDIR = ./mlx/

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L $(LIBDIR) -lft -L $(MLXDIR) -lmlx -framework OpenGL -framework Appkit

SRC = main.c move.c action.c \
	display_move.c display_str.c display_game.c \
	make_game.c check_map.c init.c util.c

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $?

$(NAME) : $(OBJS)
	make -C $(LIBDIR)
	make -C $(MLXDIR)
	$(CC) -o $(NAME) $(OBJS) -I $(INCDIR) $(LIBFLAGS) 

all :$(NAME)

clean :
	make -C $(LIBDIR) clean
	make -C $(MLXDIR) clean
	rm -f $(OBJS)

fclean : clean
	make -C $(LIBDIR) fclean
	rm -f $(NAME)

re : clean all

.PHONY	: all clean fclean re
