/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 23:48:24 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 18:14:47 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int     whitespace_action(t_param *param)
{
    param->index++;
    return (SUCCESS);
}


int     single_quote_action(t_param *param)
{
    char    *tmp = NULL;
    size_t  len = 0;
    int     i = param->index;

    //Find the next simple quote and copy all the content between the two simple quotes
    if (ft_find_char(param->input + i + 1, param->input[i], &len) == ERROR)
        return (FAILURE);
    if (!(tmp = ft_strndup(param->input + param->index, len + 2)))
        return (FAILURE);
    //Add the token to the chained list
    if (push_node(tmp, SQUOTE, &(param->l_tokens), 0) == FAILURE)
    {
        ft_strdel(&tmp);
        return (FAILURE);
    }
    ft_strdel(&tmp);
    param->index += len + 2;
    return (SUCCESS);
}

int     double_quote_action(t_param *param)
{
    int     i;
    int     length;
    char    *tmp;
    
    i = param->index + 1;
    length = 1;
    tmp = NULL;
    while (param->input[i])
    {
        length++;
        if (param->input[i] == BACKSLASH && lex_is_special_char(param->input[i + 1]))
        {
            ft_memmove(&(param->input[i]), &(param->input[i + 1]), ft_strlen(param->input + i));
        }
        else if (ft_is_double_quote(param->input[i])) // if the char is a double quote : Copy the content between the Doubles quotes
        {
            if (!(tmp = ft_strndup(param->input + param->index, length)))
                return (FAILURE);
            else
                break;
        }
        i++;
    }
    if ((push_node(tmp, DQUOTE, &(param->l_tokens), 0)) == FAILURE)
    {
        ft_strdel(&tmp);
        return (FAILURE);
    }
    ft_strdel(&tmp);
    param->index = i + 1;
    return (SUCCESS);
}


int     is_io_number(t_param *param)
{
    char    *tmp;
    int     i;

    tmp = NULL;
    i = param->index;
    while (ft_isdigit(param->input[i]))
        i++;
    if (!param->input[i] || !(ft_is_operator(param->input[i])))
        return (0);
    return (1);
}

int     operator_action(t_param *param)
{
    char    *tmp;
    int ret;
    int len;
    int size;

    tmp = NULL;
    ret = 0;
    len = 0;
    size = param->index;
    if (!(tmp = copy_until_ft(param->input + param->index, &param->index, param->ft)))
        ft_malloc_error();
    len = ft_strlen(tmp);
    if ((len <= 2) && (param->token = get_ast_op(tmp, len)) >= 0)
        ret = push_node(tmp, param->token, &(param->l_tokens), 0);
    else
    {
        param->index = size;
        ft_strdel(&tmp);
        return (UNEXPTOKEN);
    }
    ft_strdel(&tmp);
    return (ret);
}

int     identifier_action(t_param *param)
{
    char    *tmp;
    t_ope       token;

    token = WORD;
    if (!(tmp = copy_until_ft(param->input + param->index, &param->index, param->ft)))
        return (FAILURE);
    if (ft_str_isdigit(tmp))
        token = DIGIT;
    if (push_node(tmp, token, &(param->l_tokens), is_io_number(param)) == FAILURE)
    {
        ft_strdel(&tmp);
        return (FAILURE);
    }
    ft_strdel(&tmp);
    return (SUCCESS);
}