# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/12 12:42:27 by DERYCKE           #+#    #+#              #
#    Updated: 2019/01/23 17:17:24 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
LIBFT = ./libft/
LIBSH = ./libsh/
LIBNAME = ./libft/libft.a ./libsh/libsh.a

LINE_EDITION_NAME = main.c line_edition.c le_termcap.c le_termcap_tool.c le_buffer_operation.c le_cursor.c le_debug.c sh_history.c le_init.c
HISTORY_NAME = sh_history.c
LEX_PARSE_NAME = lex_utils.c lex_action.c lex_init.c parser.c parse_utils.c quotes.c

SRC = ./src

OBJ_PATH = ./obj
OBJ_NAME = $(LINE_EDITION_NAME:.c=.o) $(HISTORY_NAME:.c=.o) $(LEX_PARSE_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CPPFLAGS = -Iincludes
LDFLAGS = -Llibft -Llibsh
LDLIBS = -lft -lsh
CC = gcc
CFLAGS = -Werror -Wextra -Wall

all: compile

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -ltermcap $^ -o $@

$(OBJ_PATH)/%.o: $(SRC)/%.c
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
