# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/27 12:43:33 by kmuvezwa          #+#    #+#              #
#    Updated: 2017/09/27 14:43:40 by kmuvezwa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c\
	  ft_checks.c ft_print.c ft_prints.c ft_stats.c

OBJS = ft_ls.o\
	   ft_checks.o ft_print.o ft_prints.o ft_stats.o

LIBFT = ./libft

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) :
	make -C $(LIBFT)
	gcc -c $(FLAGS) $(SRC)
	gcc $(FLAGS) $(OBJS) -L $(LIBFT) -lft -o $(NAME)

clean :
	rm -f $(OBJS)
	@cd ./libft && $(MAKE) clean

fclean :
	rm -f $(NAME)
	rm -f $(OBJS)
	@cd ./libft && $(MAKE) fclean

re: fclean all
