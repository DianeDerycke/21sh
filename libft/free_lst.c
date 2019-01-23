/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:13:29 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/09 13:38:19 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    free_lst(t_list *lst)
{
    t_list *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        // free(tmp->content);
        tmp->content_size = 0;
        free(tmp);
        tmp = lst;
    }
}