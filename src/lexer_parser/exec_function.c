/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:50:04 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/14 16:47:21 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int     just_exec(t_ast *ast, t_sh *shell)
{
    char    *path;
    int     ret;
    
    path = NULL;
    ret = 0;
    shell->cmd = sh_rtree_to_array(ast);
	apply_expansions(shell);
	if ((exec_builtin(shell) == SUCCESS))
		return (SUCCESS);
    if ((path = ms_get_valid_cmd(shell->cmd[0], shell->env))
            && access(path, X_OK) == SUCCESS)
        execve(path, shell->cmd, shell->env);
    else if (!path)
        ret = FAILURE;
    else 
        ret = ms_perm_denied(shell->cmd[0]);
    ft_strdel(&path);
    return (ret);
}

int     exec_cmd(t_ast *ast, t_sh *shell)
{
    static int ret = 0;

    shell->cmd = sh_rtree_to_array(ast);
    apply_expansions(shell);
    if ((exec_builtin(shell)) == FAILURE)
        if ((ms_exec_binary(shell->cmd[0], shell->cmd, shell->env, shell->env)) == -1)
            ret = error_execution(shell->cmd[0]);
    sh_free_shell(shell);
    return (ret);
}