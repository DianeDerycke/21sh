/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rtree_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:14:54 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/05 00:27:04 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char    **sh_rtree_to_array(t_ast *tree)
{
    char    **array;
    int     i;

    array = NULL;
    if ((i = sh_get_size_rtree(tree)) < 0)
        return (NULL);
    if (!(array = malloc(sizeof(char*) * (i + 1))))
        return (NULL);
    i = 0;
    while (tree && tree->token == WORD)
    {
        if (!(array[i] = ft_strdup(tree->value)))
        {
            ft_free_array(array);
            return (NULL);
        }
        i++;
        tree = tree->left;
    }
    if (!(array[i] = malloc(sizeof(char) + 1)))
        return (NULL);
    array[i] = NULL;
    return (array);
}