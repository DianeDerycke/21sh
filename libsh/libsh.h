/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:09:16 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/19 15:19:57 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSH_H
# define LIBSH_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define SUCCESS		0
# define FAILURE		1
# define ERROR			-1
# define PAGAIN			1
# define ERR_INTR		-1
# define DEFAULT_HOME	"/Users/dideryck"
# define DEFAULT_PATH	"PATH=/usr/local/bin:/bin:/usr/bin:/usr/sbin:/sbin"
# define HOME			"HOME"
# define OLDPWD			"OLDPWD"
# define STR_EQUAL		"="
# define STR_DASH		"-"
# define DOLLAR			'$'
# define C_WHITESPACE	' '
# define C_DQUOTE		'"'
# define C_EQUAL		'='
# define C_TILDE		'~'
# define C_SLASH		'/'
# define VAL_SLASH		47
# define VAL_BACKSPACE	92
# define VAL_EQUAL		61
# define VAL_DASH		45
# define VAL_DOLLAR		36
# define VAL_TILDE		126
# define MS_BUFF_SIZE	1024

# ifndef PROMPT
#  define PROMPT "\033[1m\033[32m∴ ➢ \033[0m"
# endif

# define C_EQUAL		'='
# define IS_PIPE		'|'
# define HEREDOC		42
# define BUFF_SIZE		4096
# define REDIR_SIZE		15
# define SUCCESS		0
# define FAILURE		1
# define ERROR			-1
# define NOT_FOUND		0
# define ACCESS_D		1

typedef enum	e_ope {
	SEPARATOR,
	PIPE,
	WORD,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	AND,
	LESSAND,
	GREATAND,
	DIGIT,
	DQUOTE = '\"',
	SQUOTE = '\'',
}				t_ope;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_pid
{
	int				proc;
	struct s_pid	*next;
}					t_pid;

typedef struct		s_ast {
	char			*value;
	int				token;
	int				io_number;
	int				std;
	char			*heredoc;
	struct s_ast	*next;
	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

typedef struct		s_sh {
	char			**env;
	char			**cmd;
	char			*path;
	int				fork;
	struct s_pid	*l_pid;
}					t_sh;

char				**sh_get_env(void);
ssize_t				sh_read_input(char **input);
char				**sh_clean_input(char **input);
char				*sh_create_variable(char *var_name, char *var_value);
void				sh_malloc_error(void);
int					sh_binary_ex_ms(char *utility, char **split_cmd, char **env,
					char **tmp);
char				*sh_get_valid_cmd(char *cmd, char **ms_env);
char				*sh_find_path_variable(char **ms_env);
ssize_t				sh_get_cwd(char **buf);
ssize_t				sh_edit_pwd_var(char ***ms_env);
ssize_t				sh_find_variable(char *cmd, char **ms_env, size_t *index);
void				sh_edit_var(char *v_name, char *v_value, char ***env,
					size_t index);
ssize_t				sh_file_exist(const char *path);
char				*sh_get_var_value(char *var);
char				*sh_get_var_path(char *var, char **env, int *end);
char				*sh_get_var_name(char *arg, size_t end);

ssize_t				sh_command_not_found(char *cmd);
ssize_t				sh_no_such_file_or_dir(char *utility, char *cmd);
ssize_t				sh_perm_denied(char *utility);
ssize_t				sh_error_perm_denied(char *utility, char *cmd);
ssize_t				sh_undefined_variable(char *var);
ssize_t				sh_too_few_args(char *utility);
int					sh_is_env_var_name(char *str);
int					sh_simple_exec(char *utility, char **split_cmd,
					char **env, char **tmp);

int					sh_exec_binary(t_sh *shell);
int					sh_get_size_rtree(t_ast *ast);
char				**sh_rtree_to_array(t_ast *ast);
void				sh_free_shell(t_sh *shell);
char				*sh_strinsert(char *dst, char *src, int pos);
t_pid				*sh_pidnew(int pid);
int					sh_push_pidnew(int pid, t_pid **list);
void				sh_freepidlist(t_pid *list);
void				*sh_strmdel_return(char *s1, char *s2, char *s3,
					void *status);

#endif
