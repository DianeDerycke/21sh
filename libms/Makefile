# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 13:11:33 by DERYCKE           #+#    #+#              #
#    Updated: 2019/01/31 10:34:12 by DERYCKE          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libms.a

FILES = ms_clean_input ms_create_variable ms_malloc_error ms_read_input \
		ms_exec_binary ms_command_not_found ms_get_valid_cmd \
		ms_find_path_variable ms_get_env ms_no_such_file_or_dir ms_get_cwd \
		ms_edit_pwd_var ms_find_variable ms_edit_var ms_perm_denied \
		ms_file_exist ms_error_perm_denied ms_undefined_variable ms_too_few_args \
		ms_get_var_path ms_get_var_name	ms_is_env_var_name ms_simple_exec
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
	rm -rf libms.a

re: fclean all