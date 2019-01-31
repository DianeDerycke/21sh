/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:10 by dideryck          #+#    #+#             */
/*   Updated: 2019/01/31 10:38:46 by DERYCKE          ###   ########.fr       */
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

int     exec_cmd(t_ast *ast)
{
    char    **env;
    char    **cmdline;
    int     index;
    struct stat f_stat;
    static int ret = 0;

    index = 0;
    if (!(cmdline = rtree_to_array(ast)) || !(env = ms_get_env()))
        return (ERROR);
    if (apply_expansions(cmdline, env) == 1)
    {
        ft_free_array(cmdline);
        return (FAILURE);
    }
    if ((index = find_builtin(cmdline[0])) >= 0)
        ret = builtin_array[index].function(cmdline, &env, ret);
    else if (ast->pipecall == 1)
        ret = ms_simple_exec(cmdline[0], cmdline, env, env);
    else if (ast->pipecall == 0)
        ret = ms_exec_binary(cmdline[0], cmdline, env, env);
    if (ret == -1)
    {
        if (ms_file_exist(cmdline[0]) == FAILURE)
            ms_command_not_found(cmdline[0]);
        else if (lstat(cmdline[0], &f_stat) == 0 && 
                !(f_stat.st_mode & S_IXUSR))
            ms_perm_denied(cmdline[0]);
    }
    ft_free_array(cmdline);
    return (ret);
}

void    parser_execution(t_ast *ast)
{
    int     redir;

    redir = 0;
    if (!ast)
        return ;
    if (ast->token == SEPARATOR)
        parser_execution(ast->right);
    else if (ast->token == PIPE)
        exec_pipe(ast);
    else if (ast->token == WORD)
    {
        if ((redir = find_redir(ast) == SUCCESS))
            exec_redirection(ast);
        else
            exec_cmd(ast);
    }
    if (ast->token != WORD && ast->token != PIPE)
        parser_execution(ast->left);
}