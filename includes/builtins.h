/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 02:11:50 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 02:17:00 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H
#include "../libsh/libsh.h"

#define BUILTIN_SIZE 6


typedef struct      s_builtin
{
    char            name[20];
    ssize_t			(*function)(char **, char ***, int);
}                   t_builtin;

typedef struct		s_opt
{
	ssize_t			i;
	ssize_t			p;
	ssize_t			s;
	ssize_t			u;
	ssize_t			v;
}					t_opt;

ssize_t		ms_echo(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_cd(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_setenv(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_unsetenv(char **split_cmd, char ***ms_env, int ret);
ssize_t		ms_env(char **split_cmd, char ***ms_env, int ret);
ssize_t     ms_exit(char **split_cmd, char ***ms_env, int ret);

char		**find_first_bin(char **split_cmd, int c);
size_t		getnbr_args(char **split_cmd, int c);
void		copy_add_var_to_env(char ***env, char *name, char *value);
ssize_t		exec_simple_env(char **cmd, char **s_bin, char **env);
void	    init_opt_struct(t_opt *env_opt);
void		init_env_options(char **split_cmd, t_opt *env_opt);
void		valid_option(char c, t_opt *env_opt);
void		add_argument_to_env(char **split_cmd, char ***env);
char		**add_variable(char *v_name, char *v_value, char **ms_env);

int			find_builtin(char *cmd);
int     	exec_builtin(t_sh *shell);

#endif