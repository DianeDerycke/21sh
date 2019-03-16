# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 13:11:33 by DERYCKE           #+#    #+#              #
#    Updated: 2019/03/16 14:37:43 by DERYCKE          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsh.a

FILES = sh_clean_input sh_create_variable sh_malloc_error sh_read_input \
		sh_binary_ex_ms sh_command_not_found sh_get_valid_cmd \
		sh_find_path_variable sh_get_env sh_no_such_file_or_dir sh_get_cwd \
		sh_edit_pwd_var sh_find_variable sh_edit_var sh_perm_denied \
		sh_file_exist sh_error_perm_denied sh_undefined_variable sh_too_few_args \
		sh_get_var_value sh_get_var_path sh_get_var_name	sh_is_env_var_name \
		sh_simple_exec init_shell sh_free_shell sh_rtree_to_array sh_get_size_rtree sh_strinsert \
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
