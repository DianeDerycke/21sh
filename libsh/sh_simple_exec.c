/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_simple_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:14:45 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:42:00 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int		sh_simple_exec(char *utility, char **split_cmd, char **env, char **tmp)
{
	char	*path;
	int		ret;

	path = NULL;
    ret = 0;
	if ((path = sh_get_valid_cmd(utility, env))
		&& access(path, X_OK) == SUCCESS)
			ret = execve(path, split_cmd, tmp);
	else if (!path)
		return (FAILURE);
	else
		sh_perm_denied(split_cmd[0]);
	ft_strdel(&path);
	return (ret);
}