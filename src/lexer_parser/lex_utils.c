/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:55:35 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 15:57:58 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"

char    *get_operator(int index)
{
    static char     operators[20][20] = {
        {";"},
        {"|"},
        {"\n"},
        {">"},
        {">>"},
        {"<"},
        {"<<"},
        {"&"},
        {"<&"},
        {">&"},
        {"\0"},
    };
    return(operators[index]);
}

int     get_ast_op(char *c, int length)
{
    int     i;
    char    *tmp;

    i = 0;
    tmp = NULL;
    if (!c)
        return (FAILURE);
    while (i < 10)
    {
        tmp = get_operator(i);
         if (ft_strncmp(c, tmp, length) == 0)
            break;
        i++;
    }
    return (i == 10 ? -1 : i);
}

char    *copy_until_array_ft(char *s, int *start, int(*array[2])(int))
{
    char    *tmp;
    int     length;
    int     i;

    i = 0;
    tmp = NULL;
    length = 0;
    while (s[length])
    {
        i = 0;
        while (i < SIZE_CONDITION)
        {
            if (!array[i](s[length]))
                return (NULL);
            i++;
        }
        length++;
    }
    if (!(tmp = ft_strndup(s, length)))
        return (NULL);
    *start += length;
    return (tmp);
}

int     whitespace_action(t_param *param)
{
    param->index++;
    return (SUCCESS);
}