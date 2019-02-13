/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 23:48:24 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/13 12:52:53 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int(*condition[SIZE_CONDITION])(int c) = {
    &ft_is_whitespace,
    &lex_is_special_char
};

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
    if (push_node(tmp, SQUOTE, &(param->l_tokens)) == FAILURE)
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
        //if the char is BACKSLASH and the next is a special meaning char ($, \ for now) it deletes the first backslash
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
    //Add the token to the chained list
    if ((push_node(tmp, DQUOTE, &(param->l_tokens))) == FAILURE)
    {
        ft_strdel(&tmp);
        return (FAILURE);
    }
    ft_strdel(&tmp);
    param->index = i + 1;
    return (SUCCESS);
}


int     io_number_action(t_param *param)
{
    char    *tmp2;
    char    *tmp;
    size_t  len;
    int     ret;
    int     i;

    tmp2 = NULL;
    tmp = NULL;
    len = 0;
    ret = 0;
    i = param->index;
    while (ft_isdigit(param->input[i]))
        i++;
    if (!param->input[i] || !ft_is_operator(param->input[i]))
        return (FAILURE);
    if (!(tmp = ft_strndup(param->input + param->index, i - param->index)))
        return (FAILURE);
    if (!(tmp2 = copy_until_ft(param->input + i, &i, &ft_is_operator)))
        return (FAILURE);
    len = ft_strlen(tmp2);
    if (len <= 2 && len > 0 && (param->token = get_ast_op(tmp2, len) >= 0))
        ret = push_node(ft_strjoin(tmp, tmp2), IO_NUMBER, &(param->l_tokens));
    else if (len > 2)
        ret = ERROR;
    else
        ret = FAILURE;
    ft_strdel(&tmp);
    ft_strdel(&tmp2);
    if (ret == ERROR)
        return (ERROR);
    param->index = i;
    return (ret == FAILURE ? FAILURE : SUCCESS);
}

int     digit_action(t_param *param)
{
    char    *tmp;
    int     ret;

    tmp = NULL;
    ret = 0;
    if ((ret = io_number_action(param)) == SUCCESS)
        return (SUCCESS);
    else if (ret == ERROR)
        return (FAILURE);
    if (!(tmp = copy_until_ft(param->input + param->index, &param->index, param->ft)))
        return (FAILURE);
    if (push_node(tmp, DIGIT, &(param->l_tokens)) == FAILURE)
    {
        ft_strdel(&tmp);
        return (FAILURE);
    }
    ft_strdel(&tmp);
    return (SUCCESS);
}

int     operator_action(t_param *param)
{
    char *tmp = NULL;
    int ret = 0;
    int len = 0;

    //Copy until there is an operator
    if (!(tmp = copy_until_ft(param->input + param->index, &param->index, param->ft)))
        return (FAILURE);
    len = ft_strlen(tmp);
    //If the length of tmp is less/equal than 2 : Check the string if the operator exist
    //f.e : &> : The operator exist but : &&&& generates an ERROR
    if ((len <= 2) && (param->token = get_ast_op(tmp, len)) >= 0)
        ret = push_node(tmp, param->token, &(param->l_tokens));
    else
        ret = FAILURE;
    ft_strdel(&tmp);
    return (ret == FAILURE ? FAILURE : SUCCESS);
}

int     identifier_action(t_param *param)
{
    char *tmp = NULL;

    //Copy until there is a indentifier (digit, letter, allowed symbols)
    if (!(tmp = copy_until_ft(param->input + param->index, &param->index, param->ft)))
        return (FAILURE);
    //Add the token to the chained list
    if (push_node(tmp, WORD, &(param->l_tokens)) == FAILURE)
    {
        ft_strdel(&tmp);
        return (FAILURE);
    }
    ft_strdel(&tmp);
    return (SUCCESS);
}