/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_append_env_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:58:15 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/23 15:10:36 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	sh_append_env_value(char **env, char *key, char *newvalue)
{
	int		nfield;
	char	*tmp;

	nfield = sh_find_env_key(env, key);
	tmp = NULL;
	if (!env || !env[0] || !key || !newvalue || (nfield == -1))
		return ;
	if (!(tmp = ft_strdup(env[nfield])))
		ft_malloc_error();
	ft_strdel(&env[nfield]);
	if (!(env[nfield] = ft_strmjoin(tmp, ":", newvalue)))
		ft_malloc_error();
	ft_strdel(&tmp);
}
