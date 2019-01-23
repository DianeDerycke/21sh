/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:23:45 by dideryck          #+#    #+#             */
/*   Updated: 2019/01/23 14:38:17 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

static t_token     *find_priority_token(t_token *start, t_token *end)
{
    t_token     *tmp;

    tmp = NULL;
    if (!start)
        return (NULL);
    while(start != end)
    {
        if (tmp == NULL || (start->token <= tmp->token && start->token != WORD))
            tmp = start;
        start = start->next;
    }
    return (tmp);
}

t_token      *parser_input(t_token *start, t_token *end)
{
    t_token *tmp;

    tmp = NULL;
    if ((tmp = find_priority_token(start, end)))
    {
        tmp->right = parser_input(tmp->next, end);
        tmp->left = parser_input(start, tmp);
    }
    return (tmp);
}

//to do : function that free every structure and return FAILURE, to replace FAILURE with this function
