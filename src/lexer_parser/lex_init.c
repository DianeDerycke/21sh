/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 00:15:46 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/13 16:30:22 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void    free_param(t_param *param)
{

    ft_strdel(&(param->input));
    (param)->input = NULL;
    (param)->index = 0;
    (param)->token = 0;
    (param)->ft = NULL;
    (param)->l_tokens = NULL;
    free(param);
    param = NULL;
}

t_param    *init_param(void)
{
    t_param *new;

    if (!(new = malloc(sizeof(t_param))))
	    ms_malloc_error();
    (new)->input = NULL;
    (new)->index = 0;
    (new)->token = 0;
    (new)->ft = NULL;
    (new)->l_tokens = NULL;
    return (new);
}