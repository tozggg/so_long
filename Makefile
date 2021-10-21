# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 14:11:44 by taejkim           #+#    #+#              #
#    Updated: 2021/10/21 21:15:19 by taejkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_BONUS = so_long_bonus

INCDIR = ./include/
SRCDIR = ./src/
SRC_BONUSDIR = ./src_bonus/
LIBDIR = ./libft/
MLXDIR = ./mlx/

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L $(LIBDIR) -lft -L $(MLXDIR) -lmlx -framework OpenGL -framework Appkit

SRC = main.c move.c action.c \
	display_move.c display_str.c display_game.c \
	make_game.c check_map.c init.c util.c

SRC_BONUS = main_bonus.c move_bonus.c action_bonus.c \
	display_move_bonus.c display_str_bonus.c display_game_bonus.c \
	make_game_bonus.c check_map_bonus.c init_bonus.c util_bonus.c

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(SRCS:.c=.o)

SRCS_BONUS = $(addprefix $(SRC_BONUSDIR), $(SRC_BONUS))
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $?

$(NAME) : $(OBJS)
	make -C $(LIBDIR)
	make -C $(MLXDIR)
	$(CC) -o $(NAME) $(OBJS) -I $(INCDIR) $(LIBFLAGS) 

all : $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS)
	make -C $(LIBDIR)
	make -C $(MLXDIR)
	$(CC) -o $(NAME_BONUS) $(OBJS_BONUS) -I $(INCDIR) $(LIBFLAGS) 

bonus : $(NAME_BONUS)

clean :
	make -C $(LIBDIR) clean
	make -C $(MLXDIR) clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	make -C $(LIBDIR) fclean
	rm -f $(NAME) $(NAME_BONUS)

re : clean all

.PHONY : all clean fclean re bonus
