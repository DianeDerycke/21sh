/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_size_rtree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:26:26 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/11 14:54:10 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int     sh_get_size_rtree(t_ast *start, t_ast *end)
{
    int     i;

    i = 0;
    if (!start)
        return (ERROR);
    while (start != end)
    {
        start = start->left;
        i++;
    }
    return (i);
}