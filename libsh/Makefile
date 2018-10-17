# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 13:11:33 by DERYCKE           #+#    #+#              #
#    Updated: 2018/10/17 12:18:30 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsh.a

FILES = sh_strsplit sh_strfpos

SRC = $(addsuffix .c, $(FILES))
OBJ = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	gcc -c -Wall -Werror -Wextra -I . -o $@ $< 

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -rf libsh.a

re: fclean all
