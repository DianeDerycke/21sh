/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_find_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:36:27 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:40:50 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_find_variable(char *cmd, char **ms_env, size_t *index)
{
	size_t	i;

	i = 0;
	*index = 0;
	if (!cmd || !ms_env)
		return (-1);
	while (ms_env[*index])
	{
		while (ms_env[*index][i] == cmd[i] && ms_env[*index][i] != '=')
			i++;
		if (ms_env[*index][i] == '=' && (!cmd[i] || cmd[i] == VAL_BACKSPACE))
			return (0);
		(*index)++;
		i = 0;
	}
	return (-1);
}
