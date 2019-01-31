/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_var_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 16:14:28 by dideryck          #+#    #+#             */
/*   Updated: 2018/10/02 14:23:17 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static char		*ms_get_var_value(char *var)
{
	char	*path;
	size_t	i;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] != '=')
		i++;
	if (!(path = ft_strdup(var + i + 1)))
		ms_malloc_error();
	return (path);
}

char			*ms_get_var_path(char *var, char **env, int *end)
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
	var_name = ms_get_var_name(var, *end);
	if (ms_find_variable(var_name, env, &i) == SUCCESS)
	{
		ft_strdel(&var_name);
		tmp = ms_get_var_value(env[i]);
		return (tmp);
	}
	ft_strdel(&var_name);
	return (NULL);
}
