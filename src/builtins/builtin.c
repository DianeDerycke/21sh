/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:12:17 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/07 22:12:31 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

t_builtin   builtin_array[20] = {
    {"echo", ms_echo},
    {"cd", ms_cd},
    {"setenv", ms_setenv},
    {"unsetenv", ms_unsetenv},
    {"env", ms_env},
    {"exit", ms_exit},
};

int		find_builtin(char *cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (-1);
	while (i < BUILTIN_SIZE)
	{
		if (ft_strcmp(cmd, builtin_array[i].name) == SUCCESS)
			return (i);
		i++;
	}
	return (ERROR);
}

int     exec_builtin(t_sh *shell)
{
    int     index;
    int     ret;

    ret = 0;
    index = 0;
    if ((index = find_builtin(shell->cmd[0])) >= 0)
        ret = builtin_array[index].function(shell->cmd, &(shell->env), 0);
    ft_free_array(shell->cmd);
    free(shell->cmd);
    shell->cmd = NULL;
    return (SUCCESS);
}
//create array erro