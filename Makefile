# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/12 12:42:27 by DERYCKE           #+#    #+#              #
#    Updated: 2019/01/23 15:25:15 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
LIBFT = ./libft/
LIBSH = ./libsh/
LIBNAME = ./libft/libft.a ./libsh/libsh.a

LINE_EDITION_PATH = ./src/line_edition
LINE_EDITION_NAME = main.c le_termcap.c le_termcap_tool.c le_buffer_operation.c le_cursor.c le_debug.c sh_history.c le_init.c
LINE_EDITION = $(addprefix $(LINE_EDITION_PATH)/,$(LINE_EDITION_NAME))
HISTORY_PATH = ./src/history
HISTORY_NAME = sh_history.c
HISTORY = $(addprefix $(HISTORY_PATH)/,$(HISTORY_NAME))
LEX_PARSE_PATH = ./src/lexer_parser
LEX_PARSE_NAME = main.c lex_utils.c lex_action.c lex_init.c parser.c parse_utils.c quotes.c
LEX_PARSE = $(addprefix $(LEX_PARSE_PATH)/,$(LEX_PARSE_NAME))

SRC = $(LINE_EDITION) $(HISTORY) $(LEX_PARSE)

OBJ_PATH = ./obj
OBJ_NAME = $(LINE_EDITION_NAME:.c=.o) $(HISTORY_NAME:.c=.o) $(LEX_PARSE_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CPPFLAGS = -Iincludes
LDFLAGS = -Llibft -Llibsh
LTERMFLAGS = -ltermcap
LDLIBS = -lft -lsh
CC = gcc
CFLAGS = -Werror -Wextra -Wall

all: compile

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(LTERMFLAGS) $^ -o $@

$(OBJ_PATH)/%.o: $(LINE_EDITION_PATH)/%.c $(HISTORY_PATH)/%.c $(LEX_PARSE_PATH)
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
