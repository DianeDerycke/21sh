/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:12:17 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/20 16:26:24 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

t_builtin		getter_builtin(int index)
{
	static t_builtin	builtin_array[20] = {
		{"echo", ms_echo},
		{"cd", ms_cd},
		{"setenv", ms_setenv},
		{"unsetenv", ms_unsetenv},
		{"env", ms_env},
		{"exit", ms_exit},
	};

	return (builtin_array[index]);
}

int				find_builtin(char *cmd)
{
	int			i;
	t_builtin	builtin;

	i = 0;
	if (!cmd)
		return (-1);
	while (i < BUILTIN_SIZE)
	{
		builtin = getter_builtin(i);
		if (ft_strcmp(cmd, builtin.name) == SUCCESS)
			return (i);
		i++;
	}
	return (ERROR);
}

int				exec_builtin(t_sh *shell)
{
	int			index;
	int			ret;
	t_builtin	builtin;

	ret = 0;
	index = 0;
	if ((index = find_builtin(shell->cmd[0])) >= 0)
	{
		builtin = getter_builtin(index);
		ret = builtin.function(shell->cmd, &(shell->env), 0);
	}
	ft_free_array(shell->cmd);
	free(shell->cmd);
	shell->cmd = NULL;
	if (shell->fork == 0)
		exit(ret);
	return (ret);
}
