/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_push_pidnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:50:02 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 16:49:20 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int    sh_push_pidnew(int pid, t_pid **list)
{
    t_pid   *tmp;
    
    if (!list || !*list)
    {
        if (!(*list = sh_pidnew(pid)))
            return (FAILURE);
    }
    else
    {
        tmp = *list;
        while ((*list)->next)
            (*list) = (*list)->next;
        if (!((*list)->next = sh_pidnew(pid)))
            return (FAILURE);
    }
    return (SUCCESS);
}