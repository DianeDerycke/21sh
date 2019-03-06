/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_rtree_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:14:54 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/06 18:02:42 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char    **sh_rtree_to_array(t_ast *ast)
{
    char    **array;
    int     i;

    array = NULL;
    if (!ast)
        return (NULL);
    if ((i = sh_get_size_rtree(ast)) < 0)
        return (NULL);
    if (!(array = ft_memalloc(sizeof(char *) * (i + 1))))
        return (NULL);
    i = 0;
    while (ast && (ast->token == WORD || 
    ast->token == DQUOTE || ast->token == SQUOTE || (ast->token == DIGIT && ast->io_number == 0)))
    {
        if (!(array[i] = ft_strdup(ast->value)))
        {
            ft_free_array(array);
            return (NULL);
        }
        i++;
        ast = ast->left;
    }
    array[i] = NULL;
    return (array);
}