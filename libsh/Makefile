# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 13:11:33 by DERYCKE           #+#    #+#              #
#    Updated: 2018/10/24 16:07:17 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsh.a

FILES = sh_strsplit sh_strfpos sh_create_elem sh_display_prompt sh_getvalue \
		sh_get_env_value sh_add_field_array sh_find_env_key sh_append_env_value \
		sh_get_env_key sh_env_display

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
