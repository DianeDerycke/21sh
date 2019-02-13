# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/12 12:42:27 by DERYCKE           #+#    #+#              #
#    Updated: 2019/02/13 16:00:09 by DERYCKE          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
LIBFT = ./libft/
LIBSH = ./libsh/
LIBMS = ./libms/
LIBNAME = ./libft/libft.a ./libsh/libsh.a ./libms/libms.a
HISTORY = .21sh_history

LINE_EDITION_NAME = line_edition.c \
					le_termcap.c \
					le_termcap_tool.c \
					le_buffer_operation.c \
					le_cursor.c \
					le_init.c \
					le_cursor_tool.c \
					le_clipboard.c \
					le_prompt.c

HISTORY_NAME =		hy_history.c


BUILTINS_NAME =		cd.c \
					builtin.c \
					echo.c \
					env.c \
					setenv.c \
					unsetenv.c \
					init.c \
					utils2.c \

LEX_PARSE_NAME =	main.c \
					lex_input.c \
					lex_utils.c \
					lex_action.c \
					lex_init.c parser.c \
					parse_utils.c \
					parser_execution.c \
					quotes.c \
					error.c \
					expansions.c \
					exec_function.c \
					redir.c \
					pipe.c \
					redir_functions.c \


LINE_EDITION_PATH = src/line_edition/
HISTORY_PATH = src/history/
BUILTINS_PATH = src/builtins/
LEX_PARSE_PATH = src/lexer_parser/

OBJ_LINE_EDITION_PATH = obj/line_edition/
OBJ_HISTORY_PATH = obj/history/
OBJ_BUILTINS_PATH = obj/builtins/
OBJ_LEX_PARSE_PATH = obj/lexer_parser/

SRC = ./src
LINE_EDITION_SRC = $(addprefix $(LINE_EDITION_PATH), $(LINE_EDITION_NAME))
HISTORY_SRC = $(addprefix $(HISTORY_PATH), $(HISTORY_NAME))
BUILTINS_SRC = $(addprefix $(BUILTINS_PATH), $(BUILTINS_NAME))
LEX_PARSE_SRC = $(addprefix $(LEX_PARSE_PATH), $(LEX_PARSE_NAME))


OBJ = obj/
LINE_EDITION_OBJ = $(addprefix $(OBJ_LINE_EDITION_PATH), $(LINE_EDITION_NAME:.c=.o))
HISTORY_OBJ = $(addprefix $(OBJ_HISTORY_PATH), $(HISTORY_NAME:.c=.o))
BUILTINS_OBJ = $(addprefix $(OBJ_BUILTINS_PATH), $(BUILTINS_NAME:.c=.o))
LEX_PARSE_OBJ = $(addprefix $(OBJ_LEX_PARSE_PATH), $(LEX_PARSE_NAME:.c=.o))

CPPFLAGS = -Iincludes
LDFLAGS = -Llibft -Llibsh -Llibms
LDLIBS = -lft -lsh -lms
CC = gcc
CFLAGS = -Werror -Wextra -Wall
TFLAGS = -ltermcap

all: compile

$(OBJ):
	@mkdir -p $@
	mkdir $(OBJ_LINE_EDITION_PATH)
	mkdir $(OBJ_HISTORY_PATH)
	mkdir $(OBJ_BUILTINS_PATH)
	mkdir $(OBJ_LEX_PARSE_PATH)

$(OBJ_LINE_EDITION_PATH)%.o: $(LINE_EDITION_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

$(OBJ_HISTORY_PATH)%.o: $(HISTORY_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

$(OBJ_BUILTINS_PATH)%.o: $(BUILTINS_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

$(OBJ_LEX_PARSE_PATH)%.o: $(LEX_PARSE_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

$(NAME): $(OBJ) $(LINE_EDITION_OBJ) $(HISTORY_OBJ) $(BUILTINS_OBJ) $(LEX_PARSE_OBJ)
	$(CC) $(CFLAGS) -o $@ $(LINE_EDITION_OBJ) $(HISTORY_OBJ) \
	$(LEX_PARSE_OBJ) $(BUILTINS_OBJ)  $(LIBNAME) $(TFLAGS)

compile: 
	make -C $(LIBFT)
	make -C $(LIBSH)
	make -C $(LIBMS)
	make $(NAME)
	
clean:
	rm -rf $(OBJ) $(HISTORY)
	rmdir $(OBJ) 2> /dev/null || true
	make -C $(LIBFT) clean
	make -C $(LIBSH) clean
	make -C $(LIBMS) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBNAME)

re: fclean all
