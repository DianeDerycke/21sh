/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:51:19 by dideryck          #+#    #+#             */
/*   Updated: 2019/02/13 12:51:31 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

char		**find_first_bin(char **split_cmd, int c)
{
	size_t		i;

	i = 0;
	if (!split_cmd || !c)
		return (NULL);
	while (split_cmd[i] && !(ft_strchr(split_cmd[i], c)))
		i++;
	if (split_cmd[i])
		while (split_cmd[i] && ft_strchr(split_cmd[i], c))
			i++;
	if (!(split_cmd[i]))
		return (NULL);
	return (split_cmd + i);
}

size_t		getnbr_args(char **split_cmd, int c)
{
	size_t	i;

	i = 0;
	if (!split_cmd)
		return (0);
	while (split_cmd[i] && ft_strchr(split_cmd[i], c))
		i++;
	return (i);
}

void		copy_add_var_to_env(char ***env, char *name, char *value)
{
	char	**tmp;

	tmp = NULL;
	if (!(tmp = ft_copy_array(*env, ft_strlen_array(*env))))
		ms_malloc_error();
	ft_free_array(*env);
	*env = add_variable(name, value, tmp);
	ft_free_array(tmp);
}
