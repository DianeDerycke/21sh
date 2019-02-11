/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rtree_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:14:54 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/11 14:54:25 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char    **sh_rtree_to_array(t_ast *start, t_ast *end)
{
    char    **array;
    int     i;

    array = NULL;
    if ((i = sh_get_size_rtree(start, end)) < 0)
        return (NULL);
    if (!(array = malloc(sizeof(char*) * (i + 1))))
        return (NULL);
    i = 0;
    while (start && start->token == WORD && start != end)
    {
        if (!(array[i] = ft_strdup(start->value)))
        {
            ft_free_array(array);
            return (NULL);
        }
        i++;
        start = start->left;
    }
    if (!(array[i] = malloc(sizeof(char) + 1)))
        return (NULL);
    array[i] = NULL;
    return (array);
}