# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/12 12:42:27 by DERYCKE           #+#    #+#              #
#    Updated: 2018/10/16 14:47:03 by dideryck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./libft/
LIBSH = ./libsh/
LIBNAME = ./libft/libft.a ./libsh/libsh.a

SRC_PATH = ./src
SRC_NAME = main.c
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = ./obj
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CPPFLAGS = -Iincludes
LDFLAGS = -Llibft -Llibsh
LDLIBS = -lft -lms
CC = gcc
CFLAGS = -Werror -Wextra -Wall

all: compile

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

compile: 
	make -C $(LIBFT) 
	make -C $(LIBSH)
	make $(NAME)
	
clean:
	rm -f $(OBJ)
	rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C $(LIBFT) clean
	make -C $(LIBSH) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBNAME)

re: fclean all