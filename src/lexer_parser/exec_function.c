/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:50:04 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/15 15:53:53 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int     treat_quotes(t_ast *ast)
{
    while (ast)
    {
        if (ast->token == DQUOTE)
        {
            if (ft_remove_char(ast->value, '\"') == FAILURE)
                return (FAILURE);
        }
        else if (ast->token == SQUOTE)
            if (ft_remove_char(ast->value, '\'') == FAILURE)
                return (FAILURE);
        ast = ast->left;
    }
    return (SUCCESS);
}

int    treat_command(t_sh *shell, t_ast *ast)
{
    if (!ast)
        return (FAILURE);
    if (apply_expansions(shell, ast) == FAILURE)
        return (get_error(UNDEFVAR, getter_error_var(NULL)));
    if (treat_quotes(ast) == FAILURE)
        return (FAILURE);
    if (!(shell->cmd = sh_rtree_to_array(ast)))
        return (FAILURE);
    return (SUCCESS);
}

int      is_command(t_sh *shell)
{
    struct stat f_stat;
    if (find_builtin(shell->cmd[0]) >= 0)
        return (SUCCESS);
    if ((shell->path = ms_get_valid_cmd(shell->cmd[0], shell->env)) && 
        access(shell->path, X_OK) == SUCCESS)
        return (SUCCESS);
    else
    {
        ft_strdel(&(shell->path));
        if (ms_file_exist(shell->cmd[0]) && lstat(shell->cmd[0], &f_stat) == 0 &&
            !(f_stat.st_mode & S_IXUSR))
            return (get_error(PERMDENIED, shell->cmd[0]));
    }
    return (get_error(CNOTFOUND, shell->cmd[0]));
}

int     exec_cmd(t_ast *ast, t_sh *shell)
{
    int ret;

	ret = 0;
    if (!ast)
        return (FAILURE);
    if (treat_command(shell, ast) == FAILURE)
        return (FAILURE);
    if (is_command(shell) == FAILURE)
    {
        ft_free_array(shell->cmd);
        free(shell->cmd);
        shell->cmd = NULL;
        if (shell->fork == 0)
            exit (1);
        return (FAILURE);
    }
    if (!shell->path)
    {
        ret = exec_builtin(shell);
        if (shell->fork == 0)
            exit (ret);
    }
    else 
        ret = sh_exec_binary(shell);
    ft_free_array(shell->cmd);
    free(shell->cmd);
    shell->cmd = NULL;
    return (ret);
}

int     exec_pipe_cmd(t_sh *shell, t_ast *ast)
{	
	if (!ast)
		return (FAILURE);
	if (find_next_redir(ast))
		return (exec_redirection(ast, shell));
    return (exec_cmd(ast, shell));
}