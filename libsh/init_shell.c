/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:07:37 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/12 19:17:25 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

t_sh     *init_shell(void)
{
    t_sh *new;

    new = NULL;
    if (!(new = malloc(sizeof(t_sh))))
        ms_malloc_error();
    if (!(new->env = ms_get_env()))
        new->env = NULL;
    new->cmd = NULL;
    new->path = NULL;
    new->l_pid = NULL;
    new->fork = 1;
    new->heredoc = 0;
    new->pipe_heredoc = NULL;
    return (new);
}