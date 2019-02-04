/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:05:57 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/05 00:06:18 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void		sh_free_shell(t_sh *shell)
{
    if (!shell)
        return ;
    ft_free_array(shell->cmd);
    ft_free_array(shell->env);
    free(shell);
    shell = NULL;
}