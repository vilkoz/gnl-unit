# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 14:08:11 by vrybalko          #+#    #+#              #
#    Updated: 2016/12/05 15:02:54 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl_test

FLAGS = -Wall -Wextra -Werror -g

SRCS = main.c 			\
	   get_next_line.c

BINS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(BINS)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

lib:
	make -C libft/
	cp -f libft/libft.a ./

clean:
	make -C libft/ clean
	/bin/rm -f $(BINS)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

f: re
	@date
	gcc -o $(NAME) $(BINS) libft.a
	./$(NAME)
