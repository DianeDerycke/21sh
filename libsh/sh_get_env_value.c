/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 15:38:09 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/23 16:15:34 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	*sh_get_env_value(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	if (!key || !env || !env[0])
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], len))
			return (env[i] + (len + 1));
		i++;
	}
	return (NULL);
}
