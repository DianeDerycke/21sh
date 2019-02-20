/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:09:16 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/20 14:59:40 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMS_H
# define LIBMS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define PAGAIN 1
# define ERR_INTR -1
# define DEFAULT_HOME "/Users/dideryck"
# define DEFAULT_PATH "PATH=/usr/local/bin:/bin:/usr/bin:/usr/sbin:/sbin"
# define HOME "HOME"
# define OLDPWD "OLDPWD"
# define STR_EQUAL "="
# define STR_DASH "-"
# define DOLLAR '$'
# define C_WHITESPACE ' '
# define C_DQUOTE '"'
# define C_EQUAL '='
# define C_TILDE '~'
# define C_SLASH '/'
# define VAL_SLASH 47
# define VAL_BACKSPACE 92
# define VAL_EQUAL 61
# define VAL_DASH 45
# define VAL_DOLLAR 36
# define VAL_TILDE 126
# define MS_BUFF_SIZE 1024

char		**ms_get_env(void);
ssize_t		ms_read_input(char **input);
char		**ms_clean_input(char **input);
char		*ms_create_variable(char *var_name, char *var_value);
void		ms_malloc_error(void);
int			ms_exec_binary(char *utility, char **split_cmd, char **env,
					char **tmp);
char		*ms_get_valid_cmd(char *cmd, char **ms_env);
char		*ms_find_path_variable(char **ms_env);
ssize_t		ms_get_cwd(char **buf);
ssize_t		ms_edit_pwd_var(char ***ms_env);
ssize_t		ms_find_variable(char *cmd, char **ms_env, size_t *index);
void		ms_edit_var(char *v_name, char *v_value, char ***env, size_t index);
ssize_t		ms_file_exist(const char *path);
char		*ms_get_var_value(char *var);
char		*ms_get_var_path(char *var, char **env, int *end);
char		*ms_get_var_name(char *arg, size_t end);

ssize_t		ms_command_not_found(char *cmd);
ssize_t		ms_no_such_file_or_dir(char *utility, char *cmd);
ssize_t		ms_perm_denied(char *utility);
ssize_t		ms_error_perm_denied(char *utility, char *cmd);
ssize_t		ms_undefined_variable(char *var);
ssize_t		ms_too_few_args(char *utility);
int			ms_is_env_var_name(char *str);
int		ms_simple_exec(char *utility, char **split_cmd, char **env, char **tmp);


#endif
