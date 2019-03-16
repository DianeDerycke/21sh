/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_var_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 16:14:28 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:41:14 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char			*sh_get_var_path(char *var, char **env, int *end)
{
	char		*var_name;
	char		*var_path;
	char		*tmp;
	size_t		i;

	var_name = NULL;
	var_path = NULL;
	*end = 0;
	i = 0;
	tmp = NULL;
	if (!var || !env || !(*env))
		return (NULL);
	while (var[*end] && (ft_isalnum(var[*end]) ||
				var[*end] == '_'))
		(*end)++;
	var_name = sh_get_var_name(var, *end);
	if (sh_find_variable(var_name, env, &i) == SUCCESS)
	{
		ft_strdel(&var_name);
		tmp = sh_get_var_value(env[i]);
		return (tmp);
	}
	ft_strdel(&var_name);
	return (NULL);
}
