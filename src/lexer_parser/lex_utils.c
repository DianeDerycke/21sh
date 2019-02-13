/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:55:35 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/13 12:52:53 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"


int         lex_is_special_char(int c)
{
    if (!c)
        return (0);
    if (c == DOLLAR || c == BACKSLASH || c == DQUOTE)
        return (1);
    return (0);
}

int         ft_isallowedsymb(int c)
{
    if (((c > 32 && c < 49) || (c > 57 && c < 65) || (c > 90 && c < 97) || (c > 123 && c < 127)) 
            && c != DQUOTE && c != SQUOTE)
        return (1);
    return (0);
}

int     ft_is_operator(int c)
{
    int     i;

    i = 0;
    while (i < 11 && c != operators[i][0])
        i++;
    if (i == 11)
        return (0);
    return (1);
}

int     get_ast_op(char *c, int length)
{
    int     i;

    i = 0;
    if (!c)
        return (FAILURE);
    while (i < 11 && ft_strncmp(c, operators[i], length) != 0)
        i++;
    return (i == 11 ? -1 : i);
}

ssize_t     error_arg(void)
{
    ft_putendl("Number args or args unvalid");
    return (FAILURE);
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

int     ft_isidentifier(int c)
{
    if ((ft_isdigit(c) || ft_isalpha(c) || ft_isallowedsymb(c)))
        return (1);
    return (0);
}

int    push_node(char *value, int token, t_ast **node)
{
    t_ast     *tmp;
    if (!node || !*node)
    {
        if (!(*node = create_elem()))
            return (FAILURE);
        if (!((*node)->value = ft_strdup(value)))
            return (FAILURE);
        (*node)->token = token;
        (*node)->pipecall = 0;
        (*node)->next = NULL;
        (*node)->right = NULL;
        (*node)->left = NULL;
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
        (*node)->pipecall = 0;
        (*node)->next->next = NULL;
        (*node)->next->left = NULL;
        (*node)->next->left = NULL;
        *node = tmp;
    }
    return (SUCCESS);
}

int     ft_is_single_quote(int c)
{
    return (c == SQUOTE ? 1 : 0);
}

int     ft_is_double_quote(int c)
{
    return (c == DQUOTE ? 1 : 0);
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


// t_ast     *copy_list(t_ast *lst)
// {
//     t_ast     *new;

//     new = NULL;
//     while (lst)
//     {
//         if ((push_node(lst->value, lst->token, &new)) == FAILURE)
//             ft_malloc_error();
//         lst = lst->next;
//     }
//     return (new);
// }
