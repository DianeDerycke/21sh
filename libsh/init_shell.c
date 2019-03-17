/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:07:37 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 16:46:59 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

t_sh	*init_shell(void)
{
	t_sh *new;

	new = NULL;
	if (!(new = malloc(sizeof(t_sh))))
		sh_malloc_error();
	if (!(new->env = sh_get_env()))
		new->env = NULL;
	new->cmd = NULL;
	new->path = NULL;
	new->l_pid = NULL;
	new->fork = 1;
	return (new);
}
