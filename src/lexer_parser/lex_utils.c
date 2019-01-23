/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:55:35 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/18 02:10:48 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"


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
    if (c > 32 && c < 49 && c != DQUOTE && c != SQUOTE)
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

int     get_token_op(char *c, int length)
{
    int     i;

    i = 0;
    if (!c)
        return (FAILURE);
    while (i < 13 && ft_strncmp(c, operators[i], length) != 0)
        i++;
    return (i == 13 ? -1 : i);
}

ssize_t     error_arg(void)
{
    ft_putendl("Number args or args unvalid");
    return (FAILURE);
}


void    display_list(t_token *lst)
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

int    push_node(char *value, int token, t_token **current_node)
{
    t_token     *tmp;
    if (!current_node || !*current_node)
    {
        if (!(*current_node = create_elem()))
            return (FAILURE);
        if (!((*current_node)->value = ft_strdup(value)))
            return (FAILURE);
        (*current_node)->token = token;
        (*current_node)->next = NULL;
        (*current_node)->right = NULL;
        (*current_node)->left = NULL;
    }
    else
    {
        tmp = *current_node;
        while ((*current_node)->next)
            (*current_node) = (*current_node)->next;
        if (!((*current_node)->next = create_elem()))
            return (FAILURE);
        if (!((*current_node)->next->value = ft_strdup(value)))
            return (FAILURE);
        (*current_node)->next->token = token;
        (*current_node)->next->next = NULL;
        (*current_node)->next->left = NULL;
        (*current_node)->next->left = NULL;
        *current_node = tmp;
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

t_token     *create_elem(void)
{
    t_token     *new;

    if (!(new = malloc(sizeof(t_token))))
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

char    *copy_until_array_ft(char *s, int *start, int(*tab[2])(int))
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
            if (!tab[i](s[length]))
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


// t_token     *copy_list(t_token *lst)
// {
//     t_token     *new;

//     new = NULL;
//     while (lst)
//     {
//         if ((push_node(lst->value, lst->token, &new)) == FAILURE)
//             ft_malloc_error();
//         lst = lst->next;
//     }
//     return (new);
// }
