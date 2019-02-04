/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:07:37 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/05 00:16:58 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int     sh_get_shell(t_ast *ast, t_sh *shell)
{
    if (!(shell = malloc(sizeof(t_sh))))
        return (FAILURE);
    if (!(shell->cmd = sh_rtree_to_array(ast)))
        return (FAILURE);
    if (!(shell->env = ms_get_env()))
        return (FAILURE);
    return (SUCCESS);
}