# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/12 12:42:27 by DERYCKE           #+#    #+#              #
#    Updated: 2019/01/24 12:34:09 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
LIBFT = ./libft/
LIBSH = ./libsh/
LIBNAME = ./libft/libft.a ./libsh/libsh.a

LINE_EDITION_NAME = line_edition.c \
					le_termcap.c \
					le_termcap_tool.c \
					le_buffer_operation.c \
					le_cursor.c \
					le_init.c

HISTORY_NAME =		sh_history.c

LEX_PARSE_NAME =	main.c \
					lex_utils.c \
					lex_action.c \
					lex_init.c parser.c \
					parse_utils.c \
					quotes.c

LINE_EDITION_PATH = src/line_edition/
HISTORY_PATH = src/history/
LEX_PARSE_PATH = src/lexer_parser/

OBJ_LINE_EDITION_PATH = obj/line_edition/
OBJ_HISTORY_PATH = obj/history/
OBJ_LEX_PARSE_PATH = obj/lexer_parser/

SRC = ./src
LINE_EDITION_SRC = $(addprefix $(LINE_EDITION_PATH), $(LINE_EDITION_NAME))
HISTORY_SRC = $(addprefix $(HISTORY_PATH), $(HISTORY_NAME))
LEX_PARSE_SRC = $(addprefix $(LEX_PARSE_PATH), $(LEX_PARSE_NAME))


OBJ = obj/
LINE_EDITION_OBJ = $(addprefix $(OBJ_LINE_EDITION_PATH), $(LINE_EDITION_NAME:.c=.o))
HISTORY_OBJ = $(addprefix $(OBJ_HISTORY_PATH), $(HISTORY_NAME:.c=.o))
LEX_PARSE_OBJ = $(addprefix $(OBJ_LEX_PARSE_PATH), $(LEX_PARSE_NAME:.c=.o))

CPPFLAGS = -Iincludes
LDFLAGS = -Llibft -Llibsh
LDLIBS = -lft -lsh
CC = gcc
CFLAGS = -Werror -Wextra -Wall
TFLAGS = -ltermcap
all: compile

$(OBJ):
	@mkdir -p $@
	mkdir $(OBJ_LINE_EDITION_PATH)
	mkdir $(OBJ_HISTORY_PATH)
	mkdir $(OBJ_LEX_PARSE_PATH)

$(OBJ_LEX_PARSE_PATH)%.o: $(LEX_PARSE_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

$(OBJ_HISTORY_PATH)%.o: $(HISTORY_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

$(OBJ_LINE_EDITION_PATH)%.o: $(LINE_EDITION_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

$(NAME): $(OBJ) $(LINE_EDITION_OBJ) $(HISTORY_OBJ) $(LEX_PARSE_OBJ)
	$(CC) $(CFLAGS) -o $@ $(LINE_EDITION_OBJ) $(HISTORY_OBJ) $(LEX_PARSE_OBJ)
	$(LIBNAME) $(TFLAGS)

compile: 
	make -C $(LIBFT)
	make -C $(LIBSH)
	make $(NAME)
	
clean:
	rm -rf $(OBJ)
	rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C $(LIBFT) clean
	make -C $(LIBSH) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBNAME)

re: fclean all
