/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_size_rtree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:26:26 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:41:05 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int     sh_get_size_rtree(t_ast *ast)
{
    int     i;

    i = 0;
    if (!ast)
        return (ERROR);
    while (ast && ast->token >= WORD)
    {
        i++;
        ast = ast->left;
    }
    return (i);
}