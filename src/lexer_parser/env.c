/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:03:44 by dideryck          #+#    #+#             */
/*   Updated: 2019/01/31 10:38:46 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void				add_argument_to_env(char **split_cmd, char ***env)
{
	size_t	i;
	size_t	index;
	char	*var_name;
	char	*var_value;

	i = 1;
	index = 0;
	var_name = NULL;
	var_value = NULL;
	while (split_cmd[i] && !(ft_strchr(split_cmd[i], VAL_EQUAL)))
		i++;
	while (split_cmd[i] && ft_strchr(split_cmd[i], VAL_EQUAL))
	{
		ft_find_char(split_cmd[i], VAL_EQUAL, &index);
		var_name = ms_get_var_name(split_cmd[i], index);
		var_value = ft_strdup(split_cmd[i] + index + 1);
		if (ms_find_variable(var_name, *env, &index) == SUCCESS)
			ms_edit_var(var_name, var_value, env, index);
		else
			copy_add_var_to_env(env, var_name, var_value);
		ft_strdel(&var_value);
		ft_strdel(&var_name);
		i++;
	}
}

static char			**create_tmp_env(char **split_cmd)
{
	size_t		i;
	size_t		j;
	size_t		len;
	char		**tmp_env;

	i = 1;
	j = 0;
	tmp_env = NULL;
	while (split_cmd[i] && ft_strchr(split_cmd[i], VAL_DASH))
		i++;
	if (!(len = getnbr_args(split_cmd + i, VAL_EQUAL)))
		return (NULL);
	if (!(tmp_env = malloc(sizeof(char *) * (len + 1))))
		ms_malloc_error();
	while (split_cmd[i] && ft_strchr(split_cmd[i], VAL_EQUAL))
	{
		if (!(tmp_env[j] = ft_strdup(split_cmd[i])))
			ms_malloc_error();
		i++;
		j++;
	}
	tmp_env[j] = NULL;
	return (tmp_env);
}

static ssize_t		exec_env_i_opt(char **cmd, char **s_bin, char **env)
{
	char	**tmp_env;
	char	*path;
	ssize_t	ret;

	path = NULL;
	ret = 0;
	tmp_env = create_tmp_env(cmd);
	if (!(s_bin = find_first_bin(cmd, VAL_EQUAL)))
		s_bin = cmd + 2;
	if ((s_bin && *s_bin && ft_strchr(*s_bin, VAL_EQUAL)) ||
			(!s_bin || !(*s_bin)))
		ft_print_array(tmp_env);
	else if ((path = ms_find_path_variable(tmp_env)))
	{
		if (ms_exec_binary(*s_bin, s_bin, tmp_env, tmp_env) == -1)
			ret = ms_no_such_file_or_dir(cmd[0], *s_bin);
		ft_strdel(&path);
	}
	else if (ms_exec_binary(*s_bin, s_bin, env, tmp_env) == -1)
		ret = error_chdir(ERR_INTR, *s_bin, "env");
	ft_free_array(tmp_env);
	return (ret);
}

static ssize_t		apply_opt(char **cmd, t_opt opt, char **s_bin, char **env)
{
	ssize_t	ret;

	ret = 0;
	if (opt.i)
		ret = exec_env_i_opt(cmd, s_bin, env);
	else
		ret = exec_simple_env(cmd, s_bin, env);
	return (ret);
}

ssize_t				ms_env(char **split_cmd, char ***ms_env, int ret)
{
	t_opt		opt;
	char		**s_bin;

	(void)ret;
	s_bin = NULL;
	init_opt_struct(&opt);
	if (!split_cmd || !ms_env)
		return (PAGAIN);
	else if (ft_strlen_array(split_cmd) > 1)
	{
		init_env_options(split_cmd, &opt);
		if (apply_opt(split_cmd, opt, s_bin, *ms_env) == FAILURE)
			return (FAILURE);
	}
	else
		ft_print_array(*ms_env);
	return (SUCCESS);
}
