/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 00:15:46 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/02 12:32:12 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void    free_param(t_param *param)
{

    ft_strdel(&(param->input));
    param->input = NULL;
    param->index = 0;
    param->token = 0;
    param->ft = NULL;
    param->l_tokens = NULL;
    free(param);
    param = NULL;
}

t_param    *init_param(void)
{
    t_param *new;

    if (!(new = malloc(sizeof(t_param))))
	    ms_malloc_error();
    new->input = NULL;
    new->index = 0;
    new->token = 0;
    new->ft = NULL;
    new->l_tokens = NULL;
    return (new);
}

int    push_node(char *value, int token, t_ast **node, int io_nb)
{
    t_ast     *tmp;
    if (!node || !*node)
    {
        if (!(*node = create_elem()))
            return (FAILURE);
        if (!((*node)->value = ft_strdup(value)))
            return (FAILURE);
        (*node)->token = token;
        (*node)->io_number = io_nb;
    }
    else
    {
        tmp = *node;
        while ((*node)->next)
            (*node) = (*node)->next;
        if (!((*node)->next = create_elem()))
            return (FAILURE);
        if (!((*node)->next->value = ft_strdup(value)))
            return (FAILURE);
        (*node)->next->token = token;
        (*node)->next->io_number = io_nb;
        *node = tmp;
    }
    return (SUCCESS);
}

t_ast     *create_elem(void)
{
    t_ast     *new;

    if (!(new = malloc(sizeof(t_ast))))
        ft_malloc_error();
    new->value = NULL;
    new->token = 0;
    new->next = NULL;
    new->right = NULL;
    new->left = NULL;
    return (new);
}

void    display_list(t_ast *lst)
{
    if (!lst)
        printf("/!\\ LST IS NULL ERROR /!\\ \n");
    else
    {
        while (lst)
        {
            printf("----------\n");
            printf("TOKEN IS : %d\n", lst->token);
            printf("VALUE IS : %s\n", lst->value);
            printf("~~~~~~~~~~\n");
            lst = lst->next;
        }
    }
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
