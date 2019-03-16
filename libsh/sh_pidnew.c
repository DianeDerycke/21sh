/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pidnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:47:02 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:41:45 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

t_pid   *sh_pidnew(int pid)
{
    t_pid   *new;
    
    if (!(new = malloc(sizeof(t_pid))))
        ft_malloc_error();
    new->proc = pid;
    new->next = NULL;
    return (new);
}