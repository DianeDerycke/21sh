/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_freepidlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:59:51 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:13:13 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void    sh_freepidlist(t_pid **list)
{
    t_pid   *tmp;

    tmp = NULL;
    if (!list || !*list)
        return ;
    while (*list)
    {
        tmp = *list;
        *list = (*list)->next;
        free(tmp);
        tmp = NULL;
    }
    free(*list);
    *list = NULL;
    list = NULL;
}