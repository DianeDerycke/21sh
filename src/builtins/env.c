/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:03:44 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/18 14:53:46 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/error.h"

ssize_t				exec_simple_env(char **cmd, char **s_bin, char **env)
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
	if ((path = sh_find_path_variable(tmp_env)))
	{
		if (sh_binary_ex_ms(*s_bin, s_bin, tmp_env, tmp_env) == FAILURE)
			ret = sh_no_such_file_or_dir(cmd[0], *s_bin);
		ft_strdel(&path);
	}
	else if (sh_binary_ex_ms(*s_bin, s_bin, env, tmp_env) == FAILURE)
		ret = sh_no_such_file_or_dir(cmd[0], *s_bin);
	if (tmp_env)
		ft_free_array(tmp_env);
	return (ret);
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
		sh_malloc_error();
	while (split_cmd[i] && ft_strchr(split_cmd[i], VAL_EQUAL))
	{
		if (!(tmp_env[j] = ft_strdup(split_cmd[i])))
			sh_malloc_error();
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
	else if ((path = sh_find_path_variable(tmp_env)))
	{
		if (sh_binary_ex_ms(*s_bin, s_bin, tmp_env, tmp_env) == -1)
			ret = sh_no_such_file_or_dir(cmd[0], *s_bin);
		ft_strdel(&path);
	}
	else if (sh_binary_ex_ms(*s_bin, s_bin, env, tmp_env) == -1)
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
