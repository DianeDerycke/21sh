/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_size_rtree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:26:26 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/05 00:27:27 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int     sh_get_size_rtree(t_ast *lst)
{
    int     i;

    i = 0;
    if (!lst)
        return (ERROR);
    while (lst)
    {
        lst = lst->left;
        i++;
    }
    return (i);
}