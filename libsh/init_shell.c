/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:07:37 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/06 16:53:17 by dideryck         ###   ########.fr       */
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
    new->l_pid = NULL;
    return (new);
}