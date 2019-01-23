/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 00:15:46 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/11/17 01:10:54 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void    init_param(t_param **param)
{
    (*param)->input = NULL;
    (*param)->index = 0;
    (*param)->token = 0;
    (*param)->ft = NULL;
    (*param)->l_tokens = NULL;
}