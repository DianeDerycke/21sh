/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_valid_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 14:41:54 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/26 16:29:01 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_env_valid_path(char **ms_env)
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
		return (DEFAULT_PATH);
	value_path = ft_strdup(ms_env[i] + 5);
	return (value_path);
}
