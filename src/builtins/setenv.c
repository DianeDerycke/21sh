/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:03:03 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/17 02:19:05 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/error.h"

static ssize_t		is_valid_set_cmd(char **split_cmd)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 1;
	while (split_cmd[i])
	{
		if (i == 1 && ft_strchr(split_cmd[i], VAL_SLASH))
			return (FAILURE);
		if (sh_is_env_var_name(split_cmd[i]) == 1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

char				**add_variable(char *v_name, char *v_value, char **ms_env)
{
	char	**tmp_env;
	size_t	len_tmp;

	len_tmp = 0;
	if (!ms_env)
	{
		if (!(tmp_env = malloc(sizeof(char *) * 2)))
			sh_malloc_error();
		tmp_env[0] = NULL;
	}
	else if (!(tmp_env = ft_copy_array(ms_env, ft_strlen_array(ms_env) + 1)))
		sh_malloc_error();
	len_tmp = ft_strlen_array(tmp_env);
	tmp_env[len_tmp] = sh_create_variable(v_name, v_value);
	tmp_env[len_tmp + 1] = NULL;
	return (tmp_env);
}

ssize_t				ms_setenv(char **split_cmd, char ***ms_env, int ret)
{
	size_t		index;
	size_t		len_cmd;
	char		**tmp;

	(void)ret;
	index = 1;
	len_cmd = ft_strlen_array(split_cmd);
	tmp = NULL;
	if (len_cmd == 1)
		ft_print_array(*ms_env);
	else if (len_cmd > 3)
		return (too_many_args("setenv"));
	else if (len_cmd > 0 && (is_valid_set_cmd(split_cmd)) == 1)
		return (unvalid_setenv_cmd());
	else if (len_cmd > 0 &&
			sh_find_variable(split_cmd[1], *ms_env, &index) == 0)
		sh_edit_var(split_cmd[1], split_cmd[2], ms_env, index);
	else
	{
		tmp = ft_copy_array(*ms_env, ft_strlen_array(*ms_env));
		ft_free_array(*ms_env);
		*ms_env = add_variable(split_cmd[1], split_cmd[2], tmp);
		ft_free_array(tmp);
	}
	return (SUCCESS);
}
