# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 13:46:42 by yagnaou           #+#    #+#              #
#    Updated: 2022/05/19 18:09:01 by yagnaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Werror -Wextra

SRCS = *.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRCS)
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all