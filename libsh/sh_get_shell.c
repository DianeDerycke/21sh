/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:07:37 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/05 17:08:20 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

t_sh     *sh_get_shell(t_ast *ast)
{
    t_sh *new;

    new = NULL;
    if (!(new = malloc(sizeof(t_sh))))
        return (NULL);
    if (!(new->cmd = sh_rtree_to_array(ast)))
        return (NULL);
    if (!(new->env = ms_get_env()))
        return (NULL);
    return (new);
}