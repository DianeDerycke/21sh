/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:51:19 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/18 14:57:05 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char				**find_first_bin(char **split_cmd, int c)
{
	size_t		i;

	i = 0;
	if (!split_cmd || !c)
		return (NULL);
	while (split_cmd[i] && !(ft_strchr(split_cmd[i], c)))
		i++;
	if (split_cmd[i])
		while (split_cmd[i] && ft_strchr(split_cmd[i], c))
			i++;
	if (!(split_cmd[i]))
		return (NULL);
	return (split_cmd + i);
}

size_t				getnbr_args(char **split_cmd, int c)
{
	size_t	i;

	i = 0;
	if (!split_cmd)
		return (0);
	while (split_cmd[i] && ft_strchr(split_cmd[i], c))
		i++;
	return (i);
}

void				copy_add_var_to_env(char ***env, char *name, char *value)
{
	char	**tmp;

	tmp = NULL;
	if (!(tmp = ft_copy_array(*env, ft_strlen_array(*env))))
		sh_malloc_error();
	ft_free_array(*env);
	*env = add_variable(name, value, tmp);
	ft_free_array(tmp);
}

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
		var_name = sh_get_var_name(split_cmd[i], index);
		var_value = ft_strdup(split_cmd[i] + index + 1);
		if (sh_find_variable(var_name, *env, &index) == SUCCESS)
			sh_edit_var(var_name, var_value, env, index);
		else
			copy_add_var_to_env(env, var_name, var_value);
		ft_strdel(&var_value);
		ft_strdel(&var_name);
		i++;
	}
}
