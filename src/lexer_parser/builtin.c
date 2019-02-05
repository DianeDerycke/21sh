/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:12:17 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/05 17:09:39 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

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
	return (-1);
}

int     exec_builtin(t_sh *shell)
{
    int     index;
    int     ret;

    index = 0;
    ret = 0;
    if ((index = find_builtin(shell->cmd[0])) >= 0)
        ret = builtin_array[index].function(shell->cmd, &(shell->env), ret);
    else
        return (FAILURE);
    return (ret);
}

int     exec_cmd(t_ast *ast)
{
    t_sh    *shell;
    struct stat f_stat;
    static int ret = 0;

    if (!(shell = sh_get_shell(ast)))
        return (FAILURE);
    apply_expansions(shell);
    if ((ret = exec_builtin(shell)) == FAILURE)
    {
        ret = ms_exec_binary(shell->cmd[0], shell->cmd, shell->env, shell->env);
        if (ret == -1)
        {
            if (ms_file_exist(shell->cmd[0]) == FAILURE)
                ms_command_not_found(shell->cmd[0]);
            else if (lstat(shell->cmd[0], &f_stat) == 0 && 
                    !(f_stat.st_mode & S_IXUSR))
                ms_perm_denied(shell->cmd[0]);
        }
    }
    sh_free_shell(shell);
    return (ret);
}
