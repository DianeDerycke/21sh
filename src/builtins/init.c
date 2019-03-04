/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 12:44:35 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 17:20:40 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void		valid_option(char c, t_opt *env_opt)
{
	if (c == 'i')
		env_opt->i = 1;
	else if (c == 'v')
		env_opt->v = 1;
	else if (c == 'p')
		env_opt->p = 1;
	else if (c == 's')
		env_opt->s = 1;
	else if (c == 'u')
		env_opt->u = 1;
}

ssize_t		exec_simple_env(char **cmd, char **s_bin, char **env)
{
	char	**tmp_env;
	char	*path;
	ssize_t	ret;

	ret = 0;
	path = NULL;
	tmp_env = ft_copy_array(env, ft_strlen_array(env));
	add_argument_to_env(cmd, &tmp_env);
	if (!(s_bin = find_first_bin(cmd, VAL_EQUAL)))
		s_bin = cmd + 1;
	if ((path = ms_find_path_variable(tmp_env)))
	{
		if (ms_exec_binary(*s_bin, s_bin, tmp_env, tmp_env) == FAILURE)
			ret = ms_no_such_file_or_dir(cmd[0], *s_bin);
		ft_strdel(&path);
	}
	else if (ms_exec_binary(*s_bin, s_bin, env, tmp_env) == FAILURE)
		ret = ms_no_such_file_or_dir(cmd[0], *s_bin);
	if (tmp_env)
		ft_free_array(tmp_env);
	return (ret);
}

void		init_env_options(char **split_cmd, t_opt *env_opt)
{
	int		i;
	int		n;
	char	valid_opt[11];

	i = 0;
	n = 1;
	ft_strcpy(valid_opt, "iPSuv");
	while (split_cmd[n] && split_cmd[n][i] == '-')
	{
		i++;
		while (split_cmd[n][i])
		{
			if (!(ft_strchr(valid_opt, split_cmd[n][i])))
				return (error_option(split_cmd[n][i]));
			else
				valid_option(split_cmd[n][i], env_opt);
			i++;
		}
		i = 0;
		n++;
	}
}


void	init_opt_struct(t_opt *env_opt)
{
	env_opt->i = 0;
	env_opt->p = 0;
	env_opt->s = 0;
	env_opt->u = 0;
	env_opt->v = 0;
}
