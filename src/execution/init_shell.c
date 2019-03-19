/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:19:06 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/19 15:39:39 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int	edit_shlvl(t_sh *shell)
{
	size_t	index;
	char	*var_value;
	int		nb;

	var_value = NULL;
	index = 0;
	if (!shell->env || sh_find_variable("SHLVL", shell->env, &index) == ERROR)
		return (FAILURE);
	if (!(var_value = sh_get_var_value(shell->env[index])))
		return (FAILURE);
	nb = ft_atoi(var_value);
	ft_strdel(&var_value);
	var_value = ft_itoa(nb + 1);
	if (!(shell->cmd = ft_ndup_array("setenv", "SHLVL", var_value, 4)))
		sh_malloc_error();
	ft_strdel(&var_value);
	return (exec_builtin(shell));
}

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
	edit_shlvl(new);
	return (new);
}