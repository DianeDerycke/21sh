/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:55:35 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 03:11:26 by DERYCKE          ###   ########.fr       */
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

int         ft_isallowedsymb(int c)
{
    if (((c > 32 && c < 49) || (c > 57 && c < 65) || (c > 90 && c < 97) || (c >= 123 && c < 127)) 
            && c != DQUOTE && c != SQUOTE)
        return (1);
    return (0);
}

int     ft_is_operator(int c)
{
    int     i;
    char    *tmp;

    i = 0;
    while (i < 10)
    {  
        tmp = get_operator(i);
         if (c == tmp[0])
            break;
        i++;
    }
    return (i == 10 ? 0 : 1);
}

int     ft_isidentifier(int c)
{
    if (ft_is_operator(c))
        return (0);
    if ((ft_isdigit(c) || ft_isalpha(c) || ft_isallowedsymb(c)))
        return (1);
    return (0);
}

int     ft_is_single_quote(int c)
{
    return (c == SQUOTE ? 1 : 0);
}

int     ft_is_double_quote(int c)
{
    return (c == DQUOTE ? 1 : 0);
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

char    *copy_until_ft(char *s, int *start, int(*f)(int c))
{
    char    *tmp;
    int     length;

    tmp = NULL;
    length = 0;
    while (s[length] && f(s[length]) == 1)
        length++;
    if (!(tmp = ft_strndup(s, length)))
        return (NULL);
    *start += length;
    return (tmp); 
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