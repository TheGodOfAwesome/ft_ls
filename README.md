# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    README.md                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/25 08:59:46 by kmuvezwa          #+#    #+#              #
#    Updated: 2017/09/07 13:34:52 by kmuvezwa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ft_ls is a program that mimics the ls command and some of its options will allow you to find out how to interact with the file system using C. 

It deals with 

	• Management of ACL and extended attributes. 
	• Management of the columns without the option -l. (man 4 tty) 
	• Management of options -u, -f, -g, -d, ...

To compile:
	gcc -Werror -Wextra -Wall ft_ls.c -o test -L ./libft -lft
