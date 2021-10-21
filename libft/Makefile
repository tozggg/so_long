# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 14:08:11 by taejkim           #+#    #+#              #
#    Updated: 2021/10/21 14:10:16 by taejkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar -rcs
RM = rm -f

SRCS = ft_strlen.c ft_strjoin.c ft_putstr_fd.c ft_itoa.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(AR) $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
