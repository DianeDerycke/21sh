/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_env_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:29:20 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/24 15:35:05 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	*sh_get_env_key(char **env, int field)
{
	char	*tmp;
	int		i;

	if (!env || !env[0] || field < 0 || !env[field])
		return (NULL);
	tmp = env[field];
	i = sh_strfpos(env[field], '=') - 1;
	tmp[i] = '\0';
	return (tmp);
}
