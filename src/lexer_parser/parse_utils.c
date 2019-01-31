/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/31 10:38:46 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int     get_size_rtree(t_ast *lst)
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

char    **rtree_to_array(t_ast *tree)
{
    char    **array;
    int     i;

    array = NULL;
    if ((i = get_size_rtree(tree)) < 0)
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

void    display_tree(t_ast *tree, int lvl, int position)
{
    if (!tree)
        return ;
    if (position == 2)
        printf("RIGHT |  ");
    else if (position == 3)
        printf("LEFT  |  ");
    else
        printf("START  |  ");
    printf("LVL: %d --- %d ---->> %s \n",lvl, tree->token, tree->value);
    display_tree(tree->right, lvl + 1, 2);
    display_tree(tree->left, lvl + 1, 3);
}