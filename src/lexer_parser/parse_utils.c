/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/13 12:52:53 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

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