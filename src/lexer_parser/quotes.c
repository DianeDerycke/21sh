/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:17:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/31 10:38:46 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

// int    push_lst(char c, t_list **current_node)
// {
//     t_list     *tmp;
//     if (!current_node || !*current_node)
//     {
//         if (!(*current_node = ft_lstnew(value, ft_strlen(value))))
//             return (FAILURE);
//     }
//     else
//     {
//         tmp = *current_node;
//         while ((*current_node)->next)
//             (*current_node) = (*current_node)->next;
//         if (!((*current_node)->next = ft_lstnew(value, ft_strlen(value))))
//             return (FAILURE);
//         *current_node = tmp;
//     }
//     return (SUCCESS);
// }

int     valid_quotes(char *str)
{
    int     i;
    int     len;
    int     j;

    i = 0;
    len = ft_strlen(str);
    j = 0;
    if (!str)
        return (-1);
    while (str[i])
    {
        if (str[i] == DQUOTE)
        {
            i++;
            j++;
            while (str[i] && str[i] != DQUOTE)
            {
                if (str[i] && str[i] == BACKSLASH && str[i + 1])
                    i++;
                else if (!str[i + 1])
                    return (2);
                i++;
                if (!str[i])
                    return (2);
            }
            if (str[i] == DQUOTE)
                j++;
        }
        if (str[i] == SQUOTE)
        {
			j = 0;
			i++;
            while (str[i] && str[i] != SQUOTE)
                i++;
            if (!str[i] || str[i] != SQUOTE)
                return (1);
        }
        i++;
    }
    if (j % 2 > 0)
        return (2);
    return (SUCCESS);
}
//to do : valid quote should return size_t
