# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/12 12:42:27 by DERYCKE           #+#    #+#              #
#    Updated: 2019/03/14 11:43:09 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = 21sh
LIBFT = ./libft/
LIBSH = ./libsh/
LIBMS = ./libms/
LIBNAME = ./libft/libft.a ./libsh/libsh.a ./libms/libms.a
HISTORY = ~/.21sh_history

INC_DIR				=	./includes/
INC_NAME_HISTORY	=	history.h
INC_NAME_LEXER		=	lexer.h
INC_NAME_LINEEDITON	=	lineedition.h
INC_NAME_SH21		=	sh21.h

INC_HISTORY		=	$(addprefix $(INC_DIR), $(INC_NAME_HISTORY))
INC_LEXER		=	$(addprefix $(INC_DIR), $(INC_NAME_LEXER))
INC_LINEEDITON	=	$(addprefix $(INC_DIR), $(INC_NAME_LINEEDITON))
INC_SH21		=	$(addprefix $(INC_DIR), $(INC_NAME_SH21))

INC_DEPEND			= 	$(INC_HISTORY) $(INC_LEXER) $(INC_LINEEDITON) $(INC_SH21)

LINE_EDITION_NAME = line_edition.c \
					le_termcap.c \
					le_termcap_tool.c \
					le_buffer_operation.c \
					le_buffer_history.c \
					le_buffer_tool.c \
					le_cursor_motion.c \
					le_cursor_tool.c \
					le_cursor.c \
					le_init.c \
					le_exit.c \
					le_clipboard.c \
					le_prompt.c \
					le_window.c

HISTORY_NAME =		hy_history.c


BUILTINS_NAME =		cd.c \
					builtin.c \
					echo.c \
					env.c \
					setenv.c \
					unsetenv.c \
					init_builtins.c \
					utils2.c \

LEX_PARSE_NAME =	main.c \
					lex_input.c \
					lex_error.c \
					lex_utils.c \
					lex_action.c \
					init_ft.c \
					parser.c \
					parser_execution.c \
					quotes.c \
					error.c \
					expansions.c \
					exec_function.c \
					heredoc.c \
					redir.c \
					redir_utils.c \
					pipe.c \
					pipe_utils.c \
					redir_functions.c \
					signal.c \


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

OBJ_DEPEND =	$(LINE_EDITION_OBJ) $(HISTORY_OBJ) $(BUILTINS_OBJ) $(LEX_PARSE_OBJ)

CPPFLAGS		= -Iincludes
LDFLAGS			= -Llibft -Llibsh -Llibms
LDLIBS			= -lft -lsh -lms
CC				= gcc
CFLAGS			= -Werror -Wextra -Wall -g3
TFLAGS			= -ltermcap
MAKEFILE		= ./Makefile

all:	compile

$(OBJ):
	@mkdir -p $@
	@mkdir -p $(OBJ_LINE_EDITION_PATH)
	@mkdir -p $(OBJ_HISTORY_PATH)
	@mkdir -p $(OBJ_BUILTINS_PATH)
	@mkdir -p $(OBJ_LEX_PARSE_PATH) 

$(OBJ_LINE_EDITION_PATH)%.o: $(LINE_EDITION_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(OBJ_HISTORY_PATH)%.o: $(HISTORY_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(OBJ_BUILTINS_PATH)%.o: $(BUILTINS_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(OBJ_LEX_PARSE_PATH)%.o: $(LEX_PARSE_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(NAME): $(MAKEFILE) $(OBJ) $(OBJ_DEPEND) $(LIBFT) $(LIBMS) $(LIBSH)
	@$(CC) $(CFLAGS) -o $@ $(LINE_EDITION_OBJ) $(HISTORY_OBJ) \
	$(LEX_PARSE_OBJ) $(BUILTINS_OBJ)  $(LIBNAME) $(TFLAGS) \

compile:
	@printf "\033[1m\033[32m\n> 21sh Make <\n\n\033[0m"
	@make -C $(LIBFT)
	@printf "\n\033[K\033[A\033[K"
	@printf "\rLIBFT -> \033[32mDone ✓\033[0m\n"
	@make -C $(LIBSH)
	@printf "\n\033[K\033[A\033[K"
	@printf "\rLIBSH -> \033[32mDone ✓\033[0m\n"
	@make -C $(LIBMS)
	@printf "\n\033[K\033[A\033[K"
	@printf "\rLIBMS -> \033[32mDone ✓\033[0m\n"
	@make $(NAME)
	@printf "\n\033[K\033[A\033[K"
	@printf "21sh --> \033[32mDone ✓\033[0m"
	@printf "\r\n\nCompilation\033[32m Done ✓\\033[0m\n"
	
clean:
	@printf "\033[1m\033[31m\n> 21sh Make Clean <\n\n\033[0m"
	@rm -rf	$(OBJ)
	@rm -f	$(HISTORY)
	@rmdir	$(OBJ) 2> /dev/null || true
	@make -C $(LIBFT) clean
	@make -C $(LIBSH) clean
	@make -C $(LIBMS) clean
	@printf "All ---> \033[31mclean Done ✓\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBNAME)
	@printf "All ---> \033[31mfclean Done ✓\n\033[0m"

history:
	@rm -f	$(HISTORY)
	@printf "History -> \033[31mclean Done ✓\n\033[0m"

re: fclean all
