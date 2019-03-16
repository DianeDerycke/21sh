/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:05:57 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:40:53 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void		sh_free_shell(t_sh *shell)
{
    if (!shell)
        return ;
    if (shell->cmd)
        ft_free_array(shell->cmd);
    if (shell->path)
        ft_strdel(&(shell->path));
    if (shell->env)
        ft_free_array(shell->env);
    free(shell);
    shell = NULL;
}