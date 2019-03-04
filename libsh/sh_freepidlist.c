/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_freepidlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:59:51 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 15:50:10 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void    sh_freepidlist(t_pid *list)
{
    t_pid   *tmp;

    tmp = NULL;
    if (!list)
        return ;
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp);
        tmp = NULL;
    }
    list = NULL;
}