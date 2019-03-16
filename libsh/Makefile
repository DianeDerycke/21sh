# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 13:11:33 by DERYCKE           #+#    #+#              #
#    Updated: 2019/03/16 14:01:01 by DERYCKE          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsh.a

FILES = init_shell sh_free_shell sh_rtree_to_array sh_get_size_rtree sh_strinsert \
		sh_pidnew sh_push_pidnew sh_freepidlist sh_exec_binary

SRC = $(addsuffix .c, $(FILES))
OBJ = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@gcc -c -Wall -Werror -Wextra -I . -o $@ $<
	@printf "LIBSH -> \033[32m"
	@printf $<
	@printf "\033[0m\r\n"
	@printf "\033[K\r"
	@printf "\033[A"
	@printf "\033[K\r"

clean: 
	@rm -f $(OBJ)

fclean: clean
	@rm -rf libsh.a

re: fclean all
