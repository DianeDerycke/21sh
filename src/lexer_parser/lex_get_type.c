/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 15:53:43 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/17 15:55:25 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"
#include "../../includes/error.h"

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

int         ft_isallowedsymb(int c)
{
    if (((c > 32 && c < 49) || (c > 57 && c < 65) || (c > 90 && c < 97) || (c >= 123 && c < 127)) 
            && c != DQUOTE && c != SQUOTE)
        return (1);
    return (0);
}