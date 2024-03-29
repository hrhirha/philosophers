# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrhirha <hrhirha@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/26 19:38:36 by hrhirha           #+#    #+#              #
#    Updated: 2021/07/11 16:58:08 by hrhirha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -Wall -Wextra -Werror -fsanitize=address
SRCS = main.c simulation.c utils.c routine.c monitor.c

all : $(NAME)

$(NAME) : $(SRCS)
	@$(CC) -lpthread $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)

fclean: clean

re : fclean all
