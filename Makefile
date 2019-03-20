# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/20 16:33:19 by dideryck          #+#    #+#              #
#    Updated: 2019/03/20 18:04:10 by dideryck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = 21sh
LIBFT = ./libft/
LIBSH = ./libsh/
LIBNAME = ./libft/libft.a ./libsh/libsh.a
HISTORY = ~/.21sh_history

INC_DIR				  =	./includes/
INC_NAME_HISTORY	  =	history.h
INC_NAME_LEXER_PARSER =	lexer_parser.h
INC_NAME_LINEEDITON	  =	lineedition.h
INC_NAME_SH21		  =	sh21.h
INC_NAME_ERROR		  = error.h
INC_NAME_BUILTINS	  = builtins.h
INC_NAME_OPERATORS 	  =	operators.h
INC_NAME_EXECUTION	  =	execution.h
INC_NAME_PROCESS_CMD  =	process_cmd.h

INC_HISTORY		 =	$(addprefix $(INC_DIR), $(INC_NAME_HISTORY))
INC_LEXER_PARSER =	$(addprefix $(INC_DIR), $(INC_NAME_LEXER_PARSER))
INC_LINEEDITON	 =	$(addprefix $(INC_DIR), $(INC_NAME_LINEEDITON))
INC_SH21		 =	$(addprefix $(INC_DIR), $(INC_NAME_SH21))
INC_ERROR		 =	$(addprefix $(INC_DIR), $(INC_NAME_ERROR))
INC_BUILTINS	 =	$(addprefix $(INC_DIR), $(INC_NAME_BUILTINS))
INC_OPERATORS 	 = 	$(addprefix $(INC_DIR), $(INC_NAME_OPERATORS))
INC_EXECUTION 	 = 	$(addprefix $(INC_DIR), $(INC_NAME_EXECUTION))
INC_PROCESS_CMD  = 	$(addprefix $(INC_DIR), $(INC_NAME_PROCESS_CMD))

INC_DEPEND		= 	$(INC_HISTORY) $(INC_LEXER_PARSER) $(INC_LINEEDITON) \
					$(INC_SH21) $(INC_ERROR) $(INC_BUITLINS) $(INC_OPERATORS) \
					$(INC_EXECUTION) $(INC_PROCESS_CMD)

LINE_EDITION_NAME = line_edition.c \
					le_interactif_disabled.c \
					le_termcap.c \
					le_termcap_delete.c \
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
					le_prompt_tool.c \
					le_window.c

HISTORY_NAME =		hy_history.c

BUILTINS_NAME =		cd.c \
					builtin.c \
					echo.c \
					env.c \
					setenv.c \
					unsetenv.c \
					init_builtins.c \
					utils2.c

LEX_PARSE_NAME =	lex_input.c \
					lex_utils.c \
					lex_action.c \
					verify_lexer.c \
					lex_get_type.c \
					init_ft.c \
					parser.c

PROCESS_CMD_NAME = 	expansions.c \
					quotes.c

OPERATORS_NAME =	pipe.c \
					redir.c \
					redir_utils.c \
					redir_functions.c \
					heredoc.c \
					pipe_utils.c

ERROR_NAME =		error.c \
					get_error.c \
					syntax_error.c

SIGNAL_NAME    =	signal.c

EXECUTION_NAME =	init_shell.c \
					main.c \
					parser_execution.c \
					exec_function.c

LINE_EDITION_PATH = src/line_edition/
HISTORY_PATH = src/history/
BUILTINS_PATH = src/builtins/
LEX_PARSE_PATH = src/lexer_parser/
OPERATORS_PATH = src/operators/
PROCESS_CMD_PATH = src/process_cmd/
ERROR_PATH = src/error/
SIGNAL_PATH = src/signal/
EXECUTION_PATH = src/execution/

OBJ_LINE_EDITION_PATH = obj/line_edition/
OBJ_HISTORY_PATH = obj/history/
OBJ_BUILTINS_PATH = obj/builtins/
OBJ_LEX_PARSE_PATH = obj/lexer_parser/
OBJ_OPERATORS_PATH = obj/operators/
OBJ_PROCESS_CMD_PATH = obj/process_cmd/
OBJ_ERROR_PATH = obj/error/
OBJ_SIGNAL_PATH = obj/signal/
OBJ_EXECUTION_PATH = obj/execution/

SRC = ./src
LINE_EDITION_SRC = $(addprefix $(LINE_EDITION_PATH), $(LINE_EDITION_NAME))
HISTORY_SRC = $(addprefix $(HISTORY_PATH), $(HISTORY_NAME))
BUILTINS_SRC = $(addprefix $(BUILTINS_PATH), $(BUILTINS_NAME))
LEX_PARSE_SRC = $(addprefix $(LEX_PARSE_PATH), $(LEX_PARSE_NAME))
OPERATORS_SRC = $(addprefix $(OPERATORS_PATH), $(OPERATORS_NAME))
PROCESS_CMD_SRC = $(addprefix $(PROCESS_CMD_PATH), $(PROCESS_CMD_NAME))
ERROR_SRC = $(addprefix $(ERROR_PATH), $(ERROR_NAME))
SIGNAL_SRC = $(addprefix $(SIGNAL_PATH), $(SIGNAL_NAME))
EXECUTION_SRC = $(addprefix $(EXECUTION_PATH), $(EXECUTION_NAME))


OBJ = obj/
LINE_EDITION_OBJ = $(addprefix $(OBJ_LINE_EDITION_PATH), $(LINE_EDITION_NAME:.c=.o))
HISTORY_OBJ = $(addprefix $(OBJ_HISTORY_PATH), $(HISTORY_NAME:.c=.o))
BUILTINS_OBJ = $(addprefix $(OBJ_BUILTINS_PATH), $(BUILTINS_NAME:.c=.o))
LEX_PARSE_OBJ = $(addprefix $(OBJ_LEX_PARSE_PATH), $(LEX_PARSE_NAME:.c=.o))
OPERATORS_OBJ = $(addprefix $(OBJ_OPERATORS_PATH), $(OPERATORS_NAME:.c=.o))
PROCESS_CMD_OBJ = $(addprefix $(OBJ_PROCESS_CMD_PATH), $(PROCESS_CMD_NAME:.c=.o))
ERROR_OBJ = $(addprefix $(OBJ_ERROR_PATH), $(ERROR_NAME:.c=.o))
SIGNAL_OBJ = $(addprefix $(OBJ_SIGNAL_PATH), $(SIGNAL_NAME:.c=.o))
EXECUTION_OBJ = $(addprefix $(OBJ_EXECUTION_PATH), $(EXECUTION_NAME:.c=.o))

OBJ_DEPEND =	$(LINE_EDITION_OBJ) $(HISTORY_OBJ) $(BUILTINS_OBJ) $(LEX_PARSE_OBJ) $(OPERATORS_OBJ) $(PROCESS_CMD_OBJ) $(ERROR_OBJ) \
				$(SIGNAL_OBJ) $(EXECUTION_OBJ)

CPPFLAGS		= -Iincludes
LDFLAGS			= -Llibft -Llibsh
LDLIBS			= -lft -lsh
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
	@mkdir -p $(OBJ_OPERATORS_PATH)
	@mkdir -p $(OBJ_PROCESS_CMD_PATH)
	@mkdir -p $(OBJ_ERROR_PATH)
	@mkdir -p $(OBJ_SIGNAL_PATH)
	@mkdir -p $(OBJ_EXECUTION_PATH)

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


$(OBJ_OPERATORS_PATH)%.o: $(OPERATORS_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(OBJ_PROCESS_CMD_PATH)%.o: $(PROCESS_CMD_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(OBJ_ERROR_PATH)%.o: $(ERROR_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(OBJ_SIGNAL_PATH)%.o: $(SIGNAL_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(OBJ_EXECUTION_PATH)%.o: $(EXECUTION_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "21sh --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(NAME): $(MAKEFILE) $(OBJ) $(OBJ_DEPEND) $(LIBFT) $(LIBSH)
	@$(CC) $(CFLAGS) -o $@ $(LINE_EDITION_OBJ) $(HISTORY_OBJ) \
	$(LEX_PARSE_OBJ) $(BUILTINS_OBJ) $(OPERATORS_OBJ) $(PROCESS_CMD_OBJ) \
	$(ERROR_OBJ) $(SIGNAL_OBJ) $(EXECUTION_OBJ) $(LIBNAME) $(TFLAGS) \

compile:
	@printf "\033[1m\033[32m\n> 21sh Make <\n\n\033[0m"
	@make -C $(LIBFT)
	@printf "\n\033[K\033[A\033[K"
	@printf "\rLIBFT -> \033[32mDone ✓\033[0m\n"
	@make -C $(LIBSH)
	@printf "\n\033[K\033[A\033[K"
	@printf "\rLIBSH -> \033[32mDone ✓\033[0m\n"
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
	@printf "All ---> \033[31mclean Done ✓\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBNAME)
	@printf "All ---> \033[31mfclean Done ✓\n\033[0m"

history:
	@rm -f	$(HISTORY)
	@printf "History -> \033[31mclean Done ✓\n\033[0m"

re: fclean all
