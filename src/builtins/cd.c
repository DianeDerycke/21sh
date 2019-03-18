/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:01:18 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/18 14:49:45 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/error.h"

ssize_t		cd_to_env_var(char **ms_env, char *var_name)
{
	size_t		index;
	ssize_t		error;

	error = sh_find_variable(var_name, ms_env, &index);
	if (error == -1)
		return (FAILURE);
	if ((chdir(ms_env[index] + (ft_strlen(var_name) + 1)) == SUCCESS))
	{
		ft_putendl(ms_env[index] + ft_strlen(var_name) + 1);
		return (SUCCESS);
	}
	return (FAILURE);
}

ssize_t		edit_oldpwd_var(char ***ms_env, char **buf)
{
	size_t		index;

	index = 0;
	if (!buf || !(*buf))
		return (FAILURE);
	if (sh_find_variable(OLDPWD, *ms_env, &index) == -1)
		return (FAILURE);
	sh_edit_var(OLDPWD, *buf, ms_env, index);
	ft_strdel(buf);
	return (SUCCESS);
}

ssize_t		ms_cd(char **split_cmd, char ***ms_env, int ret)
{
	size_t		len_cmd;
	int			error;
	char		*buf;

	buf = NULL;
	len_cmd = ft_strlen_array(split_cmd);
	error = sh_get_cwd(&buf);
	if (len_cmd > 2)
		too_many_args("cd");
	else if (len_cmd == 1)
		ret = cd_to_env_var(*ms_env, HOME);
	else if (len_cmd == 2 && ft_strcmp(split_cmd[1], STR_DASH) == 0)
		ret = cd_to_env_var(*ms_env, OLDPWD);
	else if ((ret = chdir(split_cmd[1])) < 0)
	{
		ft_strdel(&buf);
		return (error_chdir(ret, split_cmd[1], "cd"));
	}
	if (error == FAILURE || sh_edit_pwd_var(ms_env) == FAILURE ||
	edit_oldpwd_var(ms_env, &buf) == FAILURE)
		ret = FAILURE;
	ft_strdel(&buf);
	return (ret);
}
