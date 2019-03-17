/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:03:32 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/17 02:19:12 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char		**delete_variable(char **ms_env, size_t index)
{
	size_t		i;
	size_t		j;
	char		**tmp_env;

	i = 0;
	j = 0;
	if (!(tmp_env = ft_copy_array(ms_env, ft_strlen_array(ms_env))))
		sh_malloc_error();
	ft_free_array(ms_env);
	if (!(ms_env = malloc(sizeof(char *) * (ft_strlen_array(tmp_env)))))
		sh_malloc_error();
	while (tmp_env[j])
	{
		if (i == index)
		{
			if (tmp_env[j + 1])
				j++;
			else
				break ;
		}
		ms_env[i++] = ft_strdup(tmp_env[j++]);
	}
	ms_env[i] = NULL;
	ft_free_array(tmp_env);
	return (ms_env);
}

ssize_t		ms_unsetenv(char **split_cmd, char ***ms_env, int ret)
{
	size_t	i;
	size_t	index;

	i = 1;
	index = 0;
	(void)ret;
	if (ft_strlen_array(split_cmd) == 1)
		return (sh_too_few_args("unsetenv"));
	else
		while (split_cmd[i])
		{
			if (sh_find_variable(split_cmd[i], *ms_env, &index) == -1)
				return (sh_undefined_variable(split_cmd[i]));
			else
				*ms_env = delete_variable(*ms_env, index);
			i++;
		}
	return (SUCCESS);
}
