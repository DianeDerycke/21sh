/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 00:15:46 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/31 10:38:46 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void    init_param(t_param **param)
{
    (*param)->input = NULL;
    (*param)->index = 0;
    (*param)->token = 0;
    (*param)->ft = NULL;
    (*param)->l_tokens = NULL;
}