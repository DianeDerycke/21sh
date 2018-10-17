/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:25:09 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 16:27:23 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	*sh_getvalue(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
