/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_size_rtree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:26:26 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/12 19:19:41 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int     sh_get_size_rtree(t_ast *ast)
{
    int     i;

    i = 0;
    if (!ast)
        return (ERROR);
    while (ast && (ast->token == WORD || ast->token == DIGIT))
    {
        ast = ast->left;
        i++;
    }
    return (i);
}