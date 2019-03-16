/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_find_path_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 09:28:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:40:47 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	*sh_find_path_variable(char **ms_env)
{
	int		i;
	char	*value_path;

	value_path = NULL;
	i = 0;
	if (!ms_env)
		return (NULL);
	while (ms_env[i] && ft_strncmp("PATH=", ms_env[i], 5) != 0)
		i++;
	if (ms_env[i] == NULL)
		return (NULL);
	value_path = ft_strdup(ms_env[i] + 5);
	return (value_path ? value_path : NULL);
}
