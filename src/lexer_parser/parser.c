/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:23:45 by dideryck          #+#    #+#             */
/*   Updated: 2019/02/19 12:45:00 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static t_ast     *find_priority_token(t_ast *start, t_ast *end)
{
    t_ast     *tmp;

    tmp = NULL;
    if (!start)
        return (NULL);
    while(start != end)
    {
        if (tmp == NULL || (start->token < tmp->token && start->token < WORD))
            tmp = start;
        start = start->next;
    }
    return (tmp);
}

static t_ast     *parser_left(t_ast *start, t_ast *end)
{
    t_ast     *tmp;

    tmp = NULL;
    if ((tmp = find_priority_token(start, end)))
    {
        tmp->right = parser_left(start, tmp);
        tmp->left = parser_left(tmp->next, end);
    }
    return (tmp);
}

t_ast      *create_ast(t_ast *curr_node, t_ast *start, t_ast *end)
{
    t_ast *tmp;

    tmp = NULL;
    if (start && (curr_node = find_priority_token(start, end)))
    {
        curr_node->right = parser_left(start, curr_node);
        curr_node->left = create_ast(curr_node->right, curr_node->next, end);
    }
    return (curr_node);
}

//to do : function that free every structure and return FAILURE, to replace FAILURE with this function